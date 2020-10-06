#include "Injector/Network/TCP/TcpServerSystem.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	TcpServerSystem::TcpServerSystem(
		SocketFamily family,
		const std::string& port,
		size_t _maxSessionCount) :
		tcpSocket(family, SocketProtocol::TCP),
		maxSessionCount(_maxSessionCount),
		sessions()
	{
		auto localEndpoint = Endpoint();

		if (family == SocketFamily::IPv4)
		{
			localEndpoint = Endpoint(
				Endpoint::anyAddressIPv4,
				port);
		}
		else if (family == SocketFamily::IPv6)
		{
			localEndpoint = Endpoint(
				Endpoint::anyAddressIPv6,
				port);
		}
		else
		{
			throw Exception(
				"TcpServerSystem",
				"TcpServerSystem",
				"Unspecified socket family");
		}

		tcpSocket.setBlocking(false);
		tcpSocket.bind(localEndpoint);
	}

	void TcpServerSystem::update()
	{
		auto socket = std::shared_ptr<Socket>();
		auto endpoint = Endpoint();

		if(tcpSocket.accept(socket, endpoint) &&
			sessions.size() < maxSessionCount)
		{
			auto session = createSession(
				std::move(socket),
				std::move(endpoint));
			sessions.push_back(session);
		}
	}

	void TcpServerSystem::listen()
	{
		tcpSocket.listen();
	}
}
