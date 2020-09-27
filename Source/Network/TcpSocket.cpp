#include "Injector/Network/TcpSocket.hpp"

namespace Injector
{
	asio::ip::tcp::endpoint TcpSocket::createEndpoint(
		const std::string& address,
		uint16_t port)
	{
		return asio::ip::tcp::endpoint(
			asio::ip::make_address(address), port);
	}

	const std::string TcpSocket::ipv4Any = "0.0.0.0";
	const std::string TcpSocket::ipv6Any = "::";
	const std::string TcpSocket::ipv4Loopback = "127.0.0.1";
	const std::string TcpSocket::ipv6Loopback = "::1";
}
