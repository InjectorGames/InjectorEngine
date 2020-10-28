#include "Injector/Network/TCP/TcpClient.hpp"
#include "Injector/Engine.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	void TcpClient::asyncReceiveHandle(
		const Endpoint& endpoint)
	{
		if(!socket.connect(endpoint))
		{
			running = false;
			return;
		}

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

	void TcpClient::onAsyncReceive(
		int byteCount)
	{
		lastResponseTime = Engine::getTimeNow();
	}

	TcpClient::TcpClient(
		SocketFamily family,
		size_t _receiveBufferSize) :
		socket(family, SocketProtocol::TCP),
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

	const Socket& TcpClient::getSocket() const noexcept
	{
		return socket;
	}
	double TcpClient::getLastResponseTime() const noexcept
	{
		return lastResponseTime;
	}
	bool TcpClient::isRunning() const noexcept
	{
		return running;
	}
	const std::vector<uint8_t>& TcpClient::getReceiveBuffer() const noexcept
	{
		return receiveBuffer;
	}
	const std::vector<uint8_t>& TcpClient::getSendBuffer() const noexcept
	{
		return sendBuffer;
	}

	void TcpClient::connect(
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

		receiveThread = std::thread(
			&TcpClient::asyncReceiveHandle,
			this,
			endpoint);
	}
	int TcpClient::send(
		const Datagram& datagram)
	{
		auto byteSize = datagram.getByteSize();

		if(sendBuffer.size() < byteSize)
			sendBuffer.resize(byteSize);

		datagram.writeData(sendBuffer.data());
		return socket.send(sendBuffer);
	}
}