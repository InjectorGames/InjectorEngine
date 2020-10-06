#pragma once
#include "Injector/ECS/System.hpp"
#include "Injector/Network/SocketSession.hpp"

namespace Injector
{
	class TcpServerSystem : public System
	{
	 protected:
		// Server TCP socket
		Socket tcpSocket;
		// Maximal session count
		size_t maxSessionCount;
		// Accepted socket sessions
		std::vector<std::shared_ptr<SocketSession>> sessions;

		// Socket accept handle
		virtual std::shared_ptr<SocketSession> createSession(
			std::shared_ptr<Socket> socket,
			Endpoint endpoint) = 0;
	 public:
		// Creates and binds a new TCP server system
		explicit TcpServerSystem(
			SocketFamily family,
			const std::string& port,
			size_t maxSessionCount = 256);

		void update() override;

		// Starts server listening
		void listen();
	};
}