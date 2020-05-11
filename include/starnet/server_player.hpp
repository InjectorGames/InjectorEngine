#pragma once
#include <asio.hpp>
#include <string>

namespace starnet
{
	struct ServerPlayer
	{
		uint64_t id;
		std::string username;
		asio::ip::udp::endpoint endpoint;
		uint32_t lastTicks;

		ServerPlayer(const uint64_t _id = 0,
			const std::string& _username = std::string(),
			const asio::ip::udp::endpoint& _endpoint = asio::ip::udp::endpoint(),
			const uint32_t _lastTicks = 0) :
			id(_id),
			username(_username),
			endpoint(_endpoint),
			lastTicks(_lastTicks)
		{}
	};
}
