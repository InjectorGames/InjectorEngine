#pragma once
#include "Injector/Network/Socket.hpp"

namespace Injector
{
	class SocketSession
	{
	 protected:
		// Is session still alive
		bool alive;
		// Session socket
		std::shared_ptr<Socket> socket;
		// Socket remote endpoint
		Endpoint endpoint;
	 public:
		// Creates a new socket session
		SocketSession(
			bool alive,
			const std::shared_ptr<Socket>& socket,
			const Endpoint& endpoint);
		// Closes and destroys session
		virtual ~SocketSession() = default;

		// Returns true if session is still alive
		bool isAlive() const noexcept;

		// Executes on each update cycle
		virtual void update() = 0;
	};
}
