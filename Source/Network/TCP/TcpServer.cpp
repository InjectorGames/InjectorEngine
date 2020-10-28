#include "Injector/Network/TCP/TcpServer.hpp"
#include "Injector/Engine.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	void TcpServer::asyncAcceptHandle()
	{
		while(running)
		{
			auto remoteSocket = Socket();
			auto endpoint = Endpoint();

			if(!socket.accept(remoteSocket, endpoint))
				continue;

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

			auto time = Engine::getUpdateStartTime();

			for (size_t i = 0; i < sessions.size(); i++)
			{
				auto session = sessions[i];

				if(!session->isRunning() ||
					time - session->getLastRequestTime() > requestTimeoutTime)
				{
					sessions.erase(sessions.begin() + i);
					i--;
				}
			}
		}
	}

	std::shared_ptr<TcpSession> TcpServer::createSession(
		Socket socket,
		const Endpoint& endpoint)
	{
		return std::make_shared<TcpSession>(
			std::move(socket),
			endpoint);
	}

	TcpServer::TcpServer(
		SocketFamily family,
		const std::string& port,
		size_t _maxSessionCount,
		double _requestTimeoutTime) :
		socket(family, SocketProtocol::TCP),
		maxSessionCount(_maxSessionCount),
		requestTimeoutTime(_requestTimeoutTime),
		running(false),
		acceptThread(),
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
				THIS_FUNCTION_NAME,
				"Unspecified socket family");
		}

		socket.bind(localEndpoint);
	}

	const Socket& TcpServer::getSocket() const noexcept
	{
		return socket;
	}
	size_t TcpServer::getMaxSessionCount() const noexcept
	{
		return maxSessionCount;
	}
	double TcpServer::getRequestTimeoutTime() const noexcept
	{
		return requestTimeoutTime;
	}
	bool TcpServer::isRunning() const noexcept
	{
		return running;
	}

	void TcpServer::start()
	{
		if(running)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Server is already running");
		}

		running = true;
		socket.listen();

		acceptThread = std::thread(
			&TcpServer::asyncAcceptHandle,
			this);
	}
}
