#pragma once
#include "asio.hpp"

namespace Injector
{
	class TcpSocket final
	{
	 public:
		static asio::ip::tcp::endpoint createEndpoint(
			const std::string& address,
			uint16_t port);

		static const std::string ipv4Any;
		static const std::string ipv6Any;
		static const std::string ipv4Loopback;
		static const std::string ipv6Loopback;
	};
}
