#include "Injector/Network/TcpServerSocket.hpp"
#include "Injector/Engine.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	void TcpServerSocket::asyncAcceptHandle()
	{
		while(acceptRunning.load())
		{
			auto remoteSocket = Socket();
			auto endpoint = Endpoint();

			if(!socket.accept(remoteSocket, endpoint))
			{
				onAsyncAcceptError();
				acceptRunning.store(false);
				return;
			}

			for (size_t i = 0; i < sessions.size(); i++)
			{
				auto session = sessions[i];

				if(!session->getReceiveRunning().load())
					sessions.erase(sessions.begin() + i--);
			}

			if(sessions.size() < maxSessionCount)
			{
				auto session = asyncCreateSession(
					std::move(remoteSocket),
					endpoint);

				if(session)
				{
					sessions.push_back(
						std::move(session));
				}
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
		acceptThread(),
		acceptRunning(false),
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
	TcpServerSocket::~TcpServerSocket()
	{
		acceptRunning.store(false);

		socket.shutdown(
			SocketShutdown::Both);
		socket.close();
	}

	const Socket& TcpServerSocket::getSocket() const noexcept
	{
		return socket;
	}
	const std::thread& TcpServerSocket::getAcceptThread() const noexcept
	{
		return acceptThread;
	}
	const std::atomic<bool>& TcpServerSocket::getAcceptRunning() const noexcept
	{
		return acceptRunning;
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
		if(acceptRunning.load())
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Already running");
		}

		acceptRunning.store(true);

		acceptThread = std::thread(
			&TcpServerSocket::asyncAcceptHandle,
			this);
		acceptThread.detach();
	}
	void TcpServerSocket::stop()
	{
		if(!acceptRunning.load())
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Not running");
		}

		acceptRunning.store(false);

		socket.shutdown(
			SocketShutdown::Both);
		socket.close();
	}
}
