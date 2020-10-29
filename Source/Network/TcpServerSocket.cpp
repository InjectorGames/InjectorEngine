#include "Injector/Network/TcpServerSocket.hpp"
#include "Injector/Engine.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	void TcpServerSocket::asyncAcceptHandle()
	{
		while(running)
		{
			auto remoteSocket = Socket();
			auto endpoint = Endpoint();

			if(!socket.accept(remoteSocket, endpoint))
			{
				onAsyncAcceptError();
				continue;
			}

			for (size_t i = 0; i < sessions.size(); i++)
			{
				auto session = sessions[i];

				if(!session->isRunning())
				{
					sessions.erase(sessions.begin() + i);
					i--;
				}
			}

			if(sessions.size() < maxSessionCount)
			{
				auto session = asyncCreateSession(
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
	}

	TcpServerSocket::TcpServerSocket(
		SocketFamily family,
		const std::string& port,
		size_t _maxSessionCount) :
		socket(family, SocketProtocol::TCP),
		maxSessionCount(_maxSessionCount),
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
		socket.listen();
	}

	const Socket& TcpServerSocket::getSocket() const noexcept
	{
		return socket;
	}
	bool TcpServerSocket::isRunning() const noexcept
	{
		return running;
	}
	const std::vector<std::shared_ptr<
	    TcpSessionSocket>>& TcpServerSocket::getSessions() const noexcept
	{
		return sessions;
	}

	size_t TcpServerSocket::getMaxSessionCount() const noexcept
	{
		return maxSessionCount;
	}
	void TcpServerSocket::setMaxSessionCount(size_t count) noexcept
	{
		maxSessionCount = count;
	}

	void TcpServerSocket::start()
	{
		if(running)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Server is already running");
		}

		running = true;

		acceptThread = std::thread(
			&TcpServerSocket::asyncAcceptHandle,
			this);
		acceptThread.detach();
	}
	void TcpServerSocket::stop()
	{
		if(!running)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Server is not running");
		}

		running = false;
	}
}
