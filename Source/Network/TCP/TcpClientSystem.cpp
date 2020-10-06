#include "Injector/Network/TCP/TcpClientSystem.hpp"
#include "Injector/Engine.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	TcpClientSystem::TcpClientSystem(
		SocketFamily family,
		double _timeoutTime,
		size_t receiveBufferSize) :
		tcpSocket(family, SocketProtocol::TCP),
		socketConnect(SocketConnect::Disconnected),
		timeoutTime(_timeoutTime),
		lastResponseTime(),
		receiveBuffer(receiveBufferSize)
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

		tcpSocket.setBlocking(false);
		tcpSocket.bind(localEndpoint);
	}

	void TcpClientSystem::update()
	{
		if(socketConnect == SocketConnect::Connected)
		{
			auto count = tcpSocket.receive(receiveBuffer);

			if(count > 0)
			{
				lastResponseTime = Engine::getUpdateStartTime();
				onReceive(count);
			}
			else if(Engine::getUpdateStartTime() - lastResponseTime > timeoutTime)
			{
				socketConnect = SocketConnect::Disconnected;
				onDisconnect();
			}
		}
		else if(socketConnect == SocketConnect::Connecting)
		{
			if(tcpSocket.send(nullptr, 0) == 0)
			{
				socketConnect = SocketConnect::Connected;
				lastResponseTime = Engine::getUpdateStartTime();
				onConnect(true);
			}
			else if(Engine::getUpdateStartTime() - lastResponseTime > timeoutTime)
			{
				socketConnect = SocketConnect::Disconnected;
				onConnect(false);
			}
		}
	}

	void TcpClientSystem::connect(
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

		tcpSocket.connect(endpoint);
		socketConnect = SocketConnect::Connecting;
		lastResponseTime = Engine::getUpdateStartTime();
	}
}
