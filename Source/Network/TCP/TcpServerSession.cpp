#include "Injector/Network/TcpServerSession.hpp"
#include "Injector/Engine.hpp"

namespace Injector
{
	void TcpServerSession::onReceive(int count)
	{
		lastResponseTime = Engine::getUpdateStartTime();
	}
	void TcpServerSession::onRequestTimeout()
	{
		alive = false;
		socket.shutdown(
			SocketShutdown::Both);
		socket.close();
	}

	TcpServerSession::TcpServerSession(
		Socket _socket,
		Endpoint _endpoint,
		bool _alive,
		double _timeoutTime,
		size_t receiveBufferSize) :
		alive(_alive),
		timeoutTime(_timeoutTime),
		socket(std::move(_socket)),
		endpoint(std::move(_endpoint)),
		receiveBuffer(receiveBufferSize)
	{
		lastResponseTime = Engine::getUpdateStartTime();
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

	void TcpServerSession::update()
	{
		if(Engine::getUpdateStartTime() - lastResponseTime > timeoutTime)
		{
			onRequestTimeout();
			return;
		}

		int count;

		while((count = socket.receive(receiveBuffer)) > 0)
			onReceive(count);
	}
}
