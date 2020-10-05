#include "Injector/Network/TcpClientSystem.hpp"
#include "Injector/Engine.hpp"
#include "Injector/Exception/Exception.hpp"

#include <thread>
#include <future>

namespace Injector
{
	TcpClientSystem::TcpClientSystem(
		SocketFamily family,
		double _timeoutTime) :
		tcpSocket(family, SocketProtocol::TCP),
		socketConnect(SocketConnect::NotConnected),
		timeoutTime(_timeoutTime),
		lastResponseTime()
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
				"Unspecified address family");
		}

		tcpSocket.setBlocking(false);
		tcpSocket.bind(localEndpoint);
	}

	void TcpClientSystem::update()
	{
		if(socketConnect == SocketConnect::Connected)
		{
			auto buffer = std::vector<char>(65535,'0');
			auto byteCount = tcpSocket.receive(buffer);

			if(byteCount > 0)
			{
				auto data = std::string(buffer.data());
				printf(data.c_str());
				lastResponseTime = Engine::getUpdateStartTime();
			}
		}
		else if(socketConnect == SocketConnect::ConnectInProgress)
		{
			if(tcpSocket.send(nullptr, 0) != -1)
			{
				socketConnect = SocketConnect::Connected;
				lastResponseTime = Engine::getUpdateStartTime();

				auto buffer = std::string("GET / HTTP/1.1\r\nHost: 192.168.1.1\r\n\r\n");
				auto result = tcpSocket.send(buffer.data(), buffer.size());
			}
			else if(Engine::getUpdateStartTime() - lastResponseTime > timeoutTime)
			{
				socketConnect = SocketConnect::NotConnected;
			}
		}
	}

	void TcpClientSystem::connect(
		const Endpoint& endpoint)
	{
		tcpSocket.connect(endpoint);
		socketConnect = SocketConnect::ConnectInProgress;
		lastResponseTime = Engine::getUpdateStartTime();
	}
}
