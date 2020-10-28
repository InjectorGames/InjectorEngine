#include "Injector/Network/UDP/UdpClient.hpp"
#include "Injector/Engine.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	void UdpClient::asyncReceiveHandle()
	{
		while (running)
		{
			auto byteCount = socket.receive(
				receiveBuffer);

			if (byteCount <= 0)
			{
				running = false;
				return;
			}

			onAsyncReceive(byteCount);
		}
	}

	void UdpClient::onAsyncReceive(
		int byteCount)
	{
		lastResponseTime = Engine::getTimeNow();
	}

	UdpClient::UdpClient(
		SocketFamily family,
		size_t _receiveBufferSize) :
		socket(family, SocketProtocol::UDP),
		lastResponseTime(),
		running(false),
		receiveThread(),
		receiveBuffer(_receiveBufferSize),
		sendBuffer()
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
				THIS_FUNCTION_NAME,
				"Unspecified socket family");
		}

		socket.bind(localEndpoint);
	}

	const Socket& UdpClient::getSocket() const noexcept
	{
		return socket;
	}
	double UdpClient::getLastResponseTime() const noexcept
	{
		return lastResponseTime;
	}
	bool UdpClient::isRunning() const noexcept
	{
		return running;
	}
	const std::vector<uint8_t>& UdpClient::getReceiveBuffer() const noexcept
	{
		return receiveBuffer;
	}
	const std::vector<uint8_t>& UdpClient::getSendBuffer() const noexcept
	{
		return sendBuffer;
	}

	void UdpClient::connect(
		const Endpoint& endpoint)
	{
		if(running)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Client is already running");
		}

		running = true;
		lastResponseTime = Engine::getTimeNow();

		socket.connect(endpoint);

		receiveThread = std::thread(
			&UdpClient::asyncReceiveHandle,
			this);
	}
	int UdpClient::send(
		const Datagram& datagram)
	{
		auto byteSize = datagram.getByteSize();

		if(sendBuffer.size() < byteSize)
			sendBuffer.resize(byteSize);

		datagram.writeData(sendBuffer.data());
		return socket.send(sendBuffer);
	}
}
