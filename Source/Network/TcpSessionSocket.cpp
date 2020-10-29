#include "Injector/Network/TcpSessionSocket.hpp"

namespace Injector
{
	void TcpSessionSocket::asyncReceiveHandle()
	{
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

	TcpSessionSocket::TcpSessionSocket(
		Socket _socket,
		const Endpoint& _endpoint,
		size_t _receiveBufferSize) :
		socket(std::move(_socket)),
		endpoint(_endpoint),
		running(true),
		receiveThread(&TcpSessionSocket::asyncReceiveHandle, this),
		receiveBuffer(_receiveBufferSize),
		sendBuffer()
	{
		receiveThread.detach();
	}

	const Socket& TcpSessionSocket::getSocket() const noexcept
	{
		return socket;
	}
	const Endpoint& TcpSessionSocket::getEndpoint() const noexcept
	{
		return endpoint;
	}
	bool TcpSessionSocket::isRunning() const noexcept
	{
		return running;
	}
	const std::vector<uint8_t>& TcpSessionSocket::getReceiveBuffer() const noexcept
	{
		return receiveBuffer;
	}
	const std::vector<uint8_t>& TcpSessionSocket::getSendBuffer() const noexcept
	{
		return sendBuffer;
	}

	void TcpSessionSocket::send(const Datagram& datagram)
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
}
