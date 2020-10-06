#include "Injector/Network/TCP/TcpServerSystem.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	TcpServerSystem::TcpServerSystem(
		SocketFamily family,
		const std::string& port,
		size_t _maxSessionCount) :
		socket(family, SocketProtocol::TCP),
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

		socket.setBlocking(false);
		socket.bind(localEndpoint);
	}

	const Socket& TcpServerSystem::getSocket() const noexcept
	{
		return socket;
	}
	size_t TcpServerSystem::getMaxSessionCount() const noexcept
	{
		return maxSessionCount;
	}
	const std::vector<std::shared_ptr<
		TcpServerSession>>& TcpServerSystem::getSessions() const noexcept
	{
		return sessions;
	}

	void TcpServerSystem::update()
	{
		auto remoteSocket = std::shared_ptr<Socket>();
		auto endpoint = Endpoint();

		while (socket.accept(remoteSocket, endpoint))
		{
			if(sessions.size() < maxSessionCount)
			{
				auto session = createSession(
					remoteSocket,
					endpoint);
				sessions.push_back(session);
			}
			else
			{
				remoteSocket->shutdown(
					SocketShutdown::Both);
				remoteSocket->close();
			}
		}
	}

	void TcpServerSystem::listen()
	{
		socket.listen();
	}
}
