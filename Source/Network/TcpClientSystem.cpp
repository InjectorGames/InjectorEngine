#include "Injector/Network/TcpClientSystem.hpp"
#include "Injector/Exception/Exception.hpp"

#include <thread>
#include <future>

namespace Injector
{
	TcpClientSystem::TcpClientSystem(
		SocketFamily family) :
		tcpSocket(family, SocketProtocol::TCP),
		connected(false)
	{
		auto localEndpoint = Endpoint();

		if (family == SocketFamily::IPv4)
		{
			localEndpoint = Endpoint(
				Endpoint::anyAddressIPv4,
				Endpoint::anyPortNumber);
		}
		else if (family == SocketFamily::IPv6)
		{
			localEndpoint = Endpoint(
				Endpoint::anyAddressIPv6,
				Endpoint::anyPortNumber);
		}
		else
		{
			throw Exception(
				"TcpClientSystem",
				"TcpClientSystem",
				"Unspecified address family");
		}

		tcpSocket.setBlocking(false);
		tcpSocket.bind(localEndpoint);
	}

	void TcpClientSystem::update()
	{

	}

	void TcpClientSystem::connect(
		const Endpoint& endpoint) noexcept
	{
		// TODO:
		//tcpSocket.connect();
	}
}
