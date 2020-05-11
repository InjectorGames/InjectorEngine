#pragma once
#include <starnet/datagram_type.hpp>
#include <starnet/server_player.hpp>
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
	class UdpServerSystem final : public entityx::System<UdpServerSystem>
	{
	protected:
		inline static constexpr uint32_t TimeOutTicks = 5000;

		inject::UdpSocket socket;

		uint32_t receiveTicks;
		std::vector<uint8_t> receiveBuffer;
		asio::ip::udp::endpoint receiveEndpoint;
		std::function<void(const asio::error_code&, size_t)> receiveCallback;

		size_t maxPlayerCount;
		std::vector<ServerPlayer> players;

		inline bool tryGetPlayer(const asio::ip::udp::endpoint& endpoint, ServerPlayer& _player)
		{
			for (const auto& player : players)
			{
				if (endpoint == player.endpoint)
				{
					_player = player;
					return true;
				}
			}

			return false;
		}
		inline bool tryRemovePlayer(const uint64_t id)
		{
			for (size_t i = 0; i < players.size(); i++)
			{
				const auto& player = players[i];

				if (id == player.id)
				{
					players.erase(players.begin() + i);
					return true;
				}
			}

			return false;
		}
		inline void disconnectPlayer(const ServerPlayer& player, const uint8_t reason)
		{
			// TODO: save player data

			if (tryRemovePlayer(player.id))
			{
				SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
					"Disconnected UDP server player. (id: %llu, reason: %hhu)",
					player.id, reason);
			}
			else
			{
				SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
					"Failed to disconnect UDP server player. (id: %llu, reason: %hhu)",
					player.id, reason);
			}
		}

		inline void handlePing(const UdpPingRequest& request)
		{
			auto response = UdpPingResponse(players.size(), maxPlayerCount);
			socket.sendTo(response, receiveEndpoint);
		}
		inline void handleConnect(const UdpConnectRequest& request)
		{
			uint8_t result;

			if (players.size() < maxPlayerCount)
			{
				auto player = ServerPlayer(0, request.username, receiveEndpoint, receiveTicks);
				players.push_back(player);

				SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
					"Connected UDP server player. (id: %llu, username: %s, address: %s, port: %hu)",
					player.id,player.username.c_str(),
					player.endpoint.address().to_string().c_str(), player.endpoint.port());

				result = UdpConnectResponse::Result::Connected;
			}
			else
			{
				result = UdpConnectResponse::Result::SeverIsFull;
			}

			auto response = UdpConnectResponse(result);
			socket.sendTo(response, receiveEndpoint);
		}
		inline void handleDisconnect(const UdpDisconnectRequest& request, const ServerPlayer& player)
		{
			disconnectPlayer(player, UdpDisconnectResponse::Reason::Requested);
		}
		void handleReceive(const asio::error_code& error, size_t count)
		{
			receiveTicks = static_cast<uint32_t>(SDL_GetTicks());

			if (count > 0)
			{
				try
				{
					ServerPlayer player;

					if (!tryGetPlayer(receiveEndpoint, player))
					{
						switch (receiveBuffer[0])
						{
						default:
							break;
						case static_cast<uint8_t>(DatagramType::Ping):
							handlePing(UdpPingRequest(receiveBuffer, count));
							break;
						case static_cast<uint8_t>(DatagramType::Connect):
							handleConnect(UdpConnectRequest(receiveBuffer, count));
							break;
						}
					}
					else
					{
						switch (receiveBuffer[0])
						{
						default:
							break;
						case static_cast<uint8_t>(DatagramType::Ping):
						case static_cast<uint8_t>(DatagramType::Connect):
							break;
						case static_cast<uint8_t>(DatagramType::Disconnect):
							handleDisconnect(UdpDisconnectRequest(receiveBuffer, count), player);
							break;
						}
					}
					
				}
				catch (const std::exception& exception)
				{
					SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
						"Failed to handle UDP server datagram. Error: %s", 
						exception.what());
				}
			}

			socket.asyncReceiveFrom(receiveBuffer, receiveEndpoint, receiveCallback);
		}
	public:
		UdpServerSystem(asio::io_context& context,
			const uint16_t port = 12345,
			const size_t _maxPlayerCount = 1,
			const size_t bufferSize = 0xFFFF) :
			socket(context, port),
			receiveEndpoint(),
			receiveBuffer(bufferSize),
			maxPlayerCount(_maxPlayerCount),
			players()
		{
			receiveCallback = std::bind(&UdpServerSystem::handleReceive, this,
				std::placeholders::_1, std::placeholders::_2);
		}
		virtual ~UdpServerSystem()
		{
			for (size_t i = 0; i < players.size(); i++)
				disconnectPlayer(players[i], UdpDisconnectResponse::Reason::ServerHasStopped);
		}

		void update(entityx::EntityManager& entities,
			entityx::EventManager& events,
			entityx::TimeDelta deltaTime) override
		{
			auto ticks = SDL_GetTicks();

			for (size_t i = 0; i < players.size(); i++)
			{
				const auto& player = players[i];

				if (ticks - player.lastTicks > TimeOutTicks)
					disconnectPlayer(player, UdpDisconnectResponse::Reason::RequestTimeOut);
			}
		}

		inline void start()
		{
			socket.asyncReceiveFrom(receiveBuffer, receiveEndpoint, receiveCallback);
		}
	};
}
