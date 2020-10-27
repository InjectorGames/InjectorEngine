#pragma once
#include "Injector/ECS/EcsSystem.hpp"
#include "Injector/Network/TCP/TcpServerSession.hpp"

#include <memory>

namespace Injector
{
	// Transfer Control Protocol server ECS system class
	class TcpServerEcsSystem : public EcsSystem
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
		explicit TcpServerEcsSystem(
			SocketFamily family,
			const std::string& port,
			size_t maxSessionCount = 256);

		// Returns server TCP socket
		const Socket& getSocket() const noexcept;
		// Returns server maximum session count
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