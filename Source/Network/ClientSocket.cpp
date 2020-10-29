#include "Injector/Network/ClientSocket.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	void ClientSocket::asyncReceiveHandle(
		const Endpoint& endpoint)
	{
		if(!socket.connect(endpoint))
		{
			onAsyncConnectError();
			return;
		}

		while (running)
		{
			auto byteCount = socket.receive(
				receiveBuffer);

			if (byteCount > 0)
			{
				onAsyncReceive(byteCount);
			}
			else if(byteCount == 0)
			{
				onAsyncShutdown();
			}
			else
			{
				onAsyncReceiveError();
			}
		}
	}

	ClientSocket::ClientSocket(
		SocketFamily family,
		SocketProtocol protocol,
		size_t _receiveBufferSize) :
		socket(family, protocol),
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

	Socket & ClientSocket::getSocket() noexcept
	{
		return socket;
	}
	const Socket& ClientSocket::getSocket() const noexcept
	{
		return socket;
	}

	bool ClientSocket::isRunning() const noexcept
	{
		return running;
	}
	const std::vector<uint8_t>& ClientSocket::getReceiveBuffer() const noexcept
	{
		return receiveBuffer;
	}
	const std::vector<uint8_t>& ClientSocket::getSendBuffer() const noexcept
	{
		return sendBuffer;
	}

	void ClientSocket::connect(
		const Endpoint& endpoint)
	{
		if(running)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Client is already running");
		}

		running = true;

		receiveThread = std::thread(
			&ClientSocket::asyncReceiveHandle,
			this,
			endpoint);
		receiveThread.detach();
	}

	void ClientSocket::send(
		const Datagram& datagram)
	{
		auto bufferSize =
			datagram.getDataSize() + 1;

		if(sendBuffer.size() < bufferSize)
			sendBuffer.resize(bufferSize);

		auto bufferData = sendBuffer.data();
		bufferData[0] = datagram.getType();

		datagram.writeData(
			bufferData + 1);

		auto byteCount = socket.send(
			bufferData,
			bufferSize);

		if(byteCount != bufferSize)
			onAsyncSendError(byteCount);
	}
	void ClientSocket::sendTo(
		const Datagram& datagram,
		const Endpoint& endpoint)
	{
		auto bufferSize =
			datagram.getDataSize() + 1;

		if(sendBuffer.size() < bufferSize)
			sendBuffer.resize(bufferSize);

		auto bufferData = sendBuffer.data();
		bufferData[0] = datagram.getType();

		datagram.writeData(
			bufferData + 1);

		auto byteCount = socket.sendTo(
			bufferData,
			bufferSize,
			endpoint);

		if(byteCount != bufferSize)
			onAsyncSendError(byteCount);
	}
}