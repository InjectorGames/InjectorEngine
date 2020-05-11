#pragma once
#include <starnet/datagram_type.hpp>
#include <starnet/udp_ping_request.hpp>
#include <starnet/udp_ping_response.hpp>
#include <starnet/udp_connect_request.hpp>
#include <starnet/udp_connect_response.hpp>
#include <starnet/udp_disconnect_request.hpp>
#include <starnet/udp_disconnect_response.hpp>
#include <inject/udp_socket.hpp>

#include <entityx/entityx.h>
#include <SDL.h>

namespace starnet
{
	class UdpClientSystem final : public entityx::System<UdpClientSystem>
	{
	protected:
		inject::UdpSocket socket;
		asio::ip::udp::endpoint serverEndpoint;
		std::vector<uint8_t> receiveBuffer;
		std::function<void(const asio::error_code&, size_t)> receiveCallback;

		inline void handlePing(const UdpPingResponse& response)
		{
		}
		inline void handleConnect(const UdpConnectResponse& response)
		{
		}
		void handleReceive(const asio::error_code& error, size_t count)
		{
			if (count > 0)
			{
				try
				{
					switch (receiveBuffer[0])
					{
						default:
							break;
						case static_cast<uint8_t>(DatagramType::Ping) :
							handlePing(UdpPingResponse(receiveBuffer, count));
							break;
						case static_cast<uint8_t>(DatagramType::Connect) :
							handleConnect(UdpConnectResponse(receiveBuffer, count));
							break;
					}
				}
				catch (const std::exception& exception)
				{
					SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
						"Failed to handle UDP client datagram. Error: %s",
						exception.what());
				}
			}

			socket.asyncReceive(receiveBuffer, receiveCallback);
		}
	public:
		UdpClientSystem(asio::io_context& context,
			const uint16_t port = 0,
			const size_t bufferSize = 0xFFFF) :
			socket(context, port),
			serverEndpoint(),
			receiveBuffer(bufferSize)
		{
			receiveCallback = std::bind(&UdpClientSystem::handleReceive, this,
				std::placeholders::_1, std::placeholders::_2);
		}

		void update(entityx::EntityManager& entities,
			entityx::EventManager& events,
			entityx::TimeDelta deltaTime) override
		{

		}

		inline void connect(asio::ip::udp::endpoint endpoint)
		{
			socket.connect(endpoint);
			socket.asyncReceive(receiveBuffer, receiveCallback);
			serverEndpoint = endpoint;
		}
		inline void sendPingRequest()
		{
			// TODO:
		}
		inline void sendConnectRequest(const std::string& username)
		{
			auto request = UdpConnectRequest(username);
			socket.send(request);
		}
	};
}
