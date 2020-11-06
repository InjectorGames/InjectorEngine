#include "Injector/Network/ClientSocket.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	void ClientSocket::asyncReceiveHandle(
		const Endpoint& endpoint)
	{
		if (!socket.connect(endpoint))
		{
			onAsyncConnectError();
			receiveRunning.store(false);
			return;
		}

		while (receiveRunning.load())
		{
			auto byteCount = socket.receive(
				receiveBuffer);

			if (byteCount > 0)
			{
				if (!onAsyncReceive(byteCount))
				{
					receiveRunning.store(false);
					return;
				}
			}
			else if (byteCount == 0)
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

	void ClientSocket::asyncSend(
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
	void ClientSocket::asyncSendTo(
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

	ClientSocket::ClientSocket(
		SocketFamily family,
		SocketProtocol protocol,
		size_t _receiveBufferSize) :
		socket(family, protocol),
		receiveThread(),
		receiveRunning(false),
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
	ClientSocket::~ClientSocket()
	{
		receiveRunning.store(false);

		socket.shutdown(
			SocketShutdown::Both);
		socket.close();
	}

	Socket& ClientSocket::getSocket() noexcept
	{
		return socket;
	}
	const Socket& ClientSocket::getSocket() const noexcept
	{
		return socket;
	}
	const std::thread& ClientSocket::getReceiveThread() const noexcept
	{
		return receiveThread;
	}
	const std::atomic<bool>& ClientSocket::getReceiveRunning() const noexcept
	{
		return receiveRunning;
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
		if(receiveRunning.load())
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Already running");
		}

		receiveRunning.store(true);

		receiveThread = std::thread(
			&ClientSocket::asyncReceiveHandle,
			this,
			endpoint);
		receiveThread.detach();
	}
	void ClientSocket::stop()
	{
		if(!receiveRunning.load())
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Not running");
		}

		receiveRunning.store(false);

		socket.shutdown(
			SocketShutdown::Both);
		socket.close();
	}
}