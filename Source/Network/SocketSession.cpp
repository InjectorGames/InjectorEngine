#include "Injector/Network/SocketSession.hpp"

namespace Injector
{
	SocketSession::SocketSession(
		bool _alive,
		const std::shared_ptr<Socket>& _socket,
		const Endpoint& _endpoint) :
		alive(_alive),
		socket(_socket),
		endpoint(_endpoint)
	{
	}

	bool SocketSession::isAlive() const noexcept
	{
		return alive;
	}
}
