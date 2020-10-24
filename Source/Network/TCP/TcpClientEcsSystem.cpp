#include "Injector/Network/TCP/TcpClientEcsSystem.hpp"
#include "Injector/Engine.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	void TcpClientEcsSystem::onConnect(bool result)
	{
		if(result)
		{
			socketConnect = SocketConnect::Connected;
			lastResponseTime = Engine::getUpdateStartTime();
		}
		else
		{
			socketConnect = SocketConnect::Disconnected;
		}
	}
	void TcpClientEcsSystem::onReceive(size_t byteCount)
	{
		lastResponseTime = Engine::getUpdateStartTime();
	}
	void TcpClientEcsSystem::onResponseTimeout()
	{
		socketConnect = SocketConnect::Disconnected;
	}

	TcpClientEcsSystem::TcpClientEcsSystem(
		SocketFamily family,
		double _timeoutTime,
		size_t _receiveBufferSize,
		size_t _sendBufferSize) :
		socket(family, SocketProtocol::TCP),
		socketConnect(SocketConnect::Disconnected),
		timeoutTime(_timeoutTime),
		lastResponseTime(0.0),
		receiveBuffer(_receiveBufferSize),
		sendBuffer(_sendBufferSize)
	{
		auto localEndpoint = Endpoint();

		if (family == SocketFamily::IPv4)
		{
			localEndpoint = Endpoint::anyIPv4;
		}
		else if (family == SocketFamily::IPv6)
		{
			localEndpoint = Endpoint::anyIPv6;
		}
		else
		{
			throw Exception(
				"TcpClientSystem",
				"TcpClientSystem",
				"Unspecified socket family");
		}

		socket.setBlocking(false);
		socket.bind(localEndpoint);
	}

	const Socket& TcpClientEcsSystem::getSocket() const noexcept
	{
		return socket;
	}
	SocketConnect TcpClientEcsSystem::getSocketConnect() const noexcept
	{
		return socketConnect;
	}
	double TcpClientEcsSystem::getTimeoutTime() const noexcept
	{
		return timeoutTime;
	}
	double TcpClientEcsSystem::getLastResponseTime() const noexcept
	{
		return lastResponseTime;
	}
	const std::vector<uint8_t>& TcpClientEcsSystem::getReceiveBuffer() const noexcept
	{
		return receiveBuffer;
	}

	void TcpClientEcsSystem::update()
	{
		if(socketConnect == SocketConnect::Connected)
		{
			if(Engine::getUpdateStartTime() - lastResponseTime > timeoutTime)
			{
				onResponseTimeout();
				return;
			}

			int byteCount;

			while((byteCount = socket.receive(receiveBuffer)) > 0)
				onReceive(static_cast<size_t>(byteCount));
		}
		else if(socketConnect == SocketConnect::Connecting)
		{
			if(Engine::getUpdateStartTime() - lastResponseTime > timeoutTime)
			{
				onConnect(false);
				return;
			}

			if(socket.send(nullptr, 0) == 0)
				onConnect(true);
		}
	}

	void TcpClientEcsSystem::connect(
		const Endpoint& endpoint)
	{
		if(socketConnect == SocketConnect::Connected)
		{
			throw Exception(
				"TcpClientSystem",
				"connect",
				"Already connected");
		}
		else if(socketConnect == SocketConnect::Connecting)
		{
			throw Exception(
				"TcpClientSystem",
				"connect",
				"Still in progress");
		}

		socket.connect(endpoint);
		socketConnect = SocketConnect::Connecting;
		lastResponseTime = Engine::getUpdateStartTime();
	}
}
