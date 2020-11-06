#pragma once
#include "TcpSessionSocket.hpp"
#include <memory>

namespace Injector
{
	// Transfer Control Protocol server socket class
	class TcpServerSocket
	{
	 protected:
		// Server TCP socket
		Socket socket;
		// Maximal session count
		size_t maxSessionCount;
		// Client accept thread
		std::thread acceptThread;
		// Is accept thread is still running
		std::atomic<bool> acceptRunning;

		// Accepted socket sessions
		std::vector<std::shared_ptr<
			TcpSessionSocket>> sessions;

		// Asynchronous connection accept handle
		void asyncAcceptHandle();

		// Asynchronous accept error handle
		virtual void onAsyncAcceptError() = 0;
		// Asynchronous create session handle
		virtual std::shared_ptr<TcpSessionSocket> asyncCreateSession(
			Socket socket,
			const Endpoint& endpoint) = 0;
	 public:
		// Creates and binds a new TCP server socket
		TcpServerSocket(
			SocketFamily family,
			const std::string& port,
			size_t maxSessionCount = 256);
		// Deleted copy constructor
		TcpServerSocket(const TcpServerSocket& server) = delete;
		// Closes and destroys TCP server socket
		virtual ~TcpServerSocket();

		// Returns server TCP socket
		const Socket& getSocket() const noexcept;
		// Returns server accept thread
		const std::thread& getAcceptThread() const noexcept;
		// Returns server accept running atomic
		const std::atomic<bool>& getAcceptRunning() const noexcept;
		// Returns accepted socket sessions
		const std::vector<std::shared_ptr<
			TcpSessionSocket>>& getSessions() const noexcept;

		// Returns server maximum session count
		size_t getMaxSessionCount() const noexcept;
		// Sets server maximum session count
		void setMaxSessionCount(size_t count) noexcept;

		// Starts server receive thread
		void start();
		// Stops server receive thread
		void stop();
	};
}