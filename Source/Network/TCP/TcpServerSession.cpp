#include "Injector/Network/TCP/TcpServerSession.hpp"
#include "Injector/Engine.hpp"

namespace Injector
{
	void TcpServerSession::onReceive(size_t byteCount)
	{
		lastResponseTime = Engine::getUpdateStartTime();
	}
	void TcpServerSession::onRequestTimeout()
	{
		alive = false;
	}

	TcpServerSession::TcpServerSession(
		Socket _socket,
		const Endpoint& _endpoint,
		bool _alive,
		double _timeoutTime,
		size_t _receiveBufferSize,
		size_t _sendBufferSize) :
		alive(_alive),
		timeoutTime(_timeoutTime),
		socket(std::move(_socket)),
		endpoint(_endpoint),
		receiveBuffer(_receiveBufferSize),
		sendBuffer(_sendBufferSize)
	{
		lastResponseTime = Engine::getUpdateStartTime();
	}
	TcpServerSession::~TcpServerSession()
	{
		socket.shutdown(
			SocketShutdown::Both);
		socket.close();
	}

	bool TcpServerSession::isAlive() const noexcept
	{
		return alive;
	}
	double TcpServerSession::getTimeoutTime() const noexcept
	{
		return timeoutTime;
	}
	double TcpServerSession::getLastResponseTime() const noexcept
	{
		return lastResponseTime;
	}
	const Socket& TcpServerSession::getSocket() const noexcept
	{
		return socket;
	}
	const Endpoint& TcpServerSession::getEndpoint() const noexcept
	{
		return endpoint;
	}
	const std::vector<uint8_t>& TcpServerSession::getReceiveBuffer() const noexcept
	{
		return receiveBuffer;
	}
	const std::vector<uint8_t>& TcpServerSession::getSendBuffer() const noexcept
	{
		return sendBuffer;
	}

	void TcpServerSession::update()
	{
		if(Engine::getUpdateStartTime() - lastResponseTime > timeoutTime)
		{
			onRequestTimeout();
			return;
		}

		int byteCount;

		while((byteCount = socket.receive(receiveBuffer)) > 0)
			onReceive(static_cast<size_t>(byteCount));
	}
}
