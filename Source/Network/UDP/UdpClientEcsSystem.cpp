#include "Injector/Network/UDP/UdpClientEcsSystem.hpp"
#include "Injector/Engine.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	void UdpClientEcsSystem::onReceive(size_t byteCount)
	{
		lastResponseTime = Engine::getUpdateStartTime();
	}
	void UdpClientEcsSystem::onResponseTimeout()
	{
		isConnected = false;
	}

	UdpClientEcsSystem::UdpClientEcsSystem(
		SocketFamily family,
		double _timeoutTime,
		size_t _receiveBufferSize,
		size_t _sendBufferSize) :
		socket(family, SocketProtocol::UDP),
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
				std::string(typeid(UdpClientEcsSystem).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Unspecified socket family");
		}

		socket.setBlocking(false);
		socket.bind(localEndpoint);
	}

	const Socket& UdpClientEcsSystem::getSocket() const noexcept
	{
		return socket;
	}
	double UdpClientEcsSystem::getTimeoutTime() const noexcept
	{
		return timeoutTime;
	}
	double UdpClientEcsSystem::getLastResponseTime() const noexcept
	{
		return lastResponseTime;
	}
	const std::vector<uint8_t>& UdpClientEcsSystem::getReceiveBuffer() const noexcept
	{
		return receiveBuffer;
	}
	const std::vector<uint8_t>& UdpClientEcsSystem::getSendBuffer() const noexcept
	{
		return sendBuffer;
	}

	void UdpClientEcsSystem::update()
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

	void UdpClientEcsSystem::connect(
		const Endpoint& endpoint)
	{
		socket.connect(endpoint);
		lastResponseTime = Engine::getUpdateStartTime();
		isConnected = true;
	}
}
