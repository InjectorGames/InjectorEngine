#include "Injector/Network/TCP/TcpSession.hpp"
#include "Injector/Engine.hpp"

namespace Injector
{
	void TcpSession::asyncReceiveHandle()
	{
		while (running)
		{
			auto byteCount = socket.receive(
				receiveBuffer);

			if (byteCount > 0)
				onAsyncReceive(byteCount);
		}
	}

	void TcpSession::onAsyncReceive(int byteCount)
	{
		lastRequestTime = Engine::getTimeNow();
	}

	TcpSession::TcpSession(
		Socket _socket,
		const Endpoint& _endpoint,
		size_t _receiveBufferSize) :
		socket(std::move(_socket)),
		endpoint(_endpoint),
		lastRequestTime(Engine::getTimeNow()),
		running(true),
		receiveThread(&TcpSession::asyncReceiveHandle, this),
		receiveBuffer(_receiveBufferSize),
		sendBuffer()
	{
	}

	const Socket& TcpSession::getSocket() const noexcept
	{
		return socket;
	}
	const Endpoint& TcpSession::getEndpoint() const noexcept
	{
		return endpoint;
	}
	double TcpSession::getLastRequestTime() const noexcept
	{
		return lastRequestTime;
	}
	bool TcpSession::isRunning() const noexcept
	{
		return running;
	}
	const std::vector<uint8_t>& TcpSession::getReceiveBuffer() const noexcept
	{
		return receiveBuffer;
	}
	const std::vector<uint8_t>& TcpSession::getSendBuffer() const noexcept
	{
		return sendBuffer;
	}

	int TcpSession::send(const Datagram& datagram)
	{
		if(!datagram.isValid())
		{
			throw Exception(
				std::string(typeid(TcpSession).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Datagram is not valid");
		}

		auto byteSize = datagram.getByteSize();

		if(sendBuffer.size() < byteSize)
			sendBuffer.resize(byteSize);

		datagram.writeData(sendBuffer.data());
		socket.send(sendBuffer);
	}
}
