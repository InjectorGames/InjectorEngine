#include "Injector/Network/TCP/TcpServerEcsSystem.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	std::shared_ptr<TcpServerSession> TcpServerEcsSystem::createSession(
		Socket socket,
		const Endpoint& endpoint)
	{
		return std::make_shared<TcpServerSession>(
			std::move(socket),
			endpoint);
	}

	TcpServerEcsSystem::TcpServerEcsSystem(
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

	const Socket& TcpServerEcsSystem::getSocket() const noexcept
	{
		return socket;
	}
	size_t TcpServerEcsSystem::getMaxSessionCount() const noexcept
	{
		return maxSessionCount;
	}
	const std::vector<std::shared_ptr<
		TcpServerSession>>& TcpServerEcsSystem::getSessions() const noexcept
	{
		return sessions;
	}

	void TcpServerEcsSystem::update()
	{
		auto remoteSocket = Socket();
		auto endpoint = Endpoint();

		while (socket.accept(remoteSocket, endpoint))
		{
			if(sessions.size() < maxSessionCount)
			{
				auto session = createSession(
					std::move(remoteSocket),
					endpoint);
				sessions.push_back(session);
			}
			else
			{
				remoteSocket.shutdown(
					SocketShutdown::Both);
				remoteSocket.close();
			}
		}

		for (size_t i = 0; i < sessions.size(); i++)
		{
			if(sessions[i]->isAlive())
			{
				sessions[i]->update();
			}
			else
			{
				sessions.erase(
					sessions.begin() + i);
				i--;
			}
		}
	}

	void TcpServerEcsSystem::listen()
	{
		socket.listen();
	}
}
