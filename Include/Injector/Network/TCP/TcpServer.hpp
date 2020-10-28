#pragma once
#include "Injector/Network/TCP/TcpSession.hpp"
#include <memory>

namespace Injector
{
	// Transfer Control Protocol server class
	class TcpServer
	{
	 protected:
		// Server TCP socket
		Socket socket;
		// Maximal session count
		size_t maxSessionCount;
		// Client request timeout time
		double requestTimeoutTime;
		// Is server still running
		bool running;
		// Client accept thread
		std::thread acceptThread;

		// Accepted socket sessions
		std::vector<std::shared_ptr<
			TcpSession>> sessions;

		// Asynchronous connection accept handle
		void asyncAcceptHandle();

		// Create session handle
		virtual std::shared_ptr<TcpSession> createSession(
			Socket socket,
			const Endpoint& endpoint);
	 public:
		// Creates and binds a new TCP server
		TcpServer(
			SocketFamily family,
			const std::string& port,
			size_t maxSessionCount = 256,
			double requestTimeoutTime = 6.0);
		// Deleted copy constructor
		TcpServer(const TcpServer& server) = delete;

		// Returns server TCP socket
		const Socket& getSocket() const noexcept;
		// Returns server maximum session count
		size_t getMaxSessionCount() const noexcept;
		// Returns session timeout time
		double getRequestTimeoutTime() const noexcept;
		// Returns true if server is still running
		bool isRunning() const noexcept;

		// Starts server listening
		void start();
	};
}