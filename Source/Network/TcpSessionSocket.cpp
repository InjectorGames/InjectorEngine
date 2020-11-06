#include "Injector/Network/TcpSessionSocket.hpp"

namespace Injector
{
	void TcpSessionSocket::asyncReceiveHandle()
	{
		while (receiveRunning.load())
		{
			auto byteCount = socket.receive(
				receiveBuffer);

			if (byteCount > 0)
			{
				if(!onAsyncReceive(byteCount))
				{
					receiveRunning.store(false);
					return;
				}
			}
			else if(byteCount == 0)
			{
				onAsyncShutdown();
				receiveRunning.store(false);
				return;
			}
			else
			{
				onAsyncReceiveError();
				receiveRunning.store(false);
				return;
			}
		}
	}

	void TcpSessionSocket::asyncSend(const Datagram& datagram)
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

	TcpSessionSocket::TcpSessionSocket(
		Socket _socket,
		const Endpoint& _endpoint,
		size_t _receiveBufferSize) :
		socket(std::move(_socket)),
		endpoint(_endpoint),
		receiveThread(&TcpSessionSocket::asyncReceiveHandle, this),
		receiveRunning(true),
		receiveBuffer(_receiveBufferSize),
		sendBuffer()
	{
		receiveThread.detach();
	}
	TcpSessionSocket::~TcpSessionSocket()
	{
		receiveRunning.store(false);

		socket.shutdown(
			SocketShutdown::Both);
		socket.close();
	}

	const Socket& TcpSessionSocket::getSocket() const noexcept
	{
		return socket;
	}
	const Endpoint& TcpSessionSocket::getEndpoint() const noexcept
	{
		return endpoint;
	}
	const std::thread& TcpSessionSocket::getReceiveThread() const noexcept
	{
		return receiveThread;
	}
	const std::atomic<bool>& TcpSessionSocket::getReceiveRunning() const noexcept
	{
		return receiveRunning;
	}
	const std::vector<uint8_t>& TcpSessionSocket::getReceiveBuffer() const noexcept
	{
		return receiveBuffer;
	}
	const std::vector<uint8_t>& TcpSessionSocket::getSendBuffer() const noexcept
	{
		return sendBuffer;
	}
}
