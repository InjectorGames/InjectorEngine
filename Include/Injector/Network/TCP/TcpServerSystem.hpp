#pragma once
#include "Injector/ECS/System.hpp"
#include "Injector/Network/TcpServerSession.hpp"

#include <memory>

namespace Injector
{
	class TcpServerSystem : public System
	{
	 protected:
		// Server TCP socket
		Socket socket;
		// Maximal session count
		size_t maxSessionCount;
		// Accepted socket sessions
		std::vector<std::shared_ptr<
			TcpServerSession>> sessions;

		// Socket accept handle
		virtual std::shared_ptr<TcpServerSession> createSession(
			Socket socket,
			const Endpoint& endpoint);
	 public:
		// Creates and binds a new TCP server system
		explicit TcpServerSystem(
			SocketFamily family,
			const std::string& port,
			size_t maxSessionCount = 256);

		// Returns server socket
		const Socket& getSocket() const noexcept;
		// Returns server maximal session count
		size_t getMaxSessionCount() const noexcept;
		// Returns server sessions
		const std::vector<std::shared_ptr<
			TcpServerSession>>& getSessions() const noexcept;

		// Executes on each update cycle
		void update() override;

		// Starts server listening
		void listen();
	};
}