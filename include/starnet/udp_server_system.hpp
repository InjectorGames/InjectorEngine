#pragma once
#include <starnet/datagram_type.hpp>
#include <starnet/server_player.hpp>
#include <starnet/udp_ping_response.hpp>
#include <starnet/udp_connect_request.hpp>
#include <starnet/udp_connect_response.hpp>
#include <inject/udp_socket.hpp>

#include <entityx/entityx.h>

namespace starnet
{
	class UdpServerSystem final : public entityx::System<UdpServerSystem>
	{
	protected:
		inject::UdpSocket socket;
		size_t maxPlayerCount;
		std::vector<ServerPlayer> players;

		inline void handlePing()
		{
			auto response = UdpPingResponse(players.size(), maxPlayerCount);
			//sendTo(response, endpoint);
		}
		inline void handleConnect(const UdpConnectRequest& request)
		{
			uint8_t result;

			if (players.size() < maxPlayerCount)
			{
				SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
					"[UdpServer]: Connected player. (username: %s)", request.username.c_str());

				result = UdpConnectResponse::Result::Connected;
			}
			else
			{
				result = UdpConnectResponse::Result::SeverIsFull;
			}

			auto response = UdpConnectResponse(result);
			//sendTo(response, endpoint);
		}
		void onReceive(const size_t count)
		{

			/*if (count > 0)
			{
				switch (buffer[0])
				{
				default:
					break;
				case static_cast<uint8_t>(DatagramType::Ping):
					if(count == 2)
						handlePing();
					break;
				case static_cast<uint8_t>(DatagramType::Connect):
					if(count == UdpConnectRequest::size)
						handleConnect(UdpConnectRequest(buffer));
					break;
				}
			}*/

			//asyncReceive();
		}
	public:
		UdpServerSystem(const uint16_t port = 12345,
			const size_t _maxPlayerCount = 1) :
			socket(port),
			maxPlayerCount(_maxPlayerCount),
			players()
		{}

		void update(entityx::EntityManager& entities,
			entityx::EventManager& events,
			entityx::TimeDelta deltaTime) override
		{

		}
	};
}
