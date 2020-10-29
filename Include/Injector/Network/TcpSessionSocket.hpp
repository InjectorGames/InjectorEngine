#pragma once
#include "Injector/Network/Socket.hpp"
#include "Injector/Network/Datagram.hpp"

#include <thread>

namespace Injector
{
	// Transfer Control Protocol session class
	class TcpSessionSocket
	{
	 protected:
		// Client socket
		Socket socket;
		// Client remote endpoint
		Endpoint endpoint;
		// Is session still running
		bool running;
		// Message receive thread
		std::thread receiveThread;
		// Message receive buffer
		std::vector<uint8_t> receiveBuffer;
		// Message send buffer
		std::vector<uint8_t> sendBuffer;

		// Asynchronous message receive handle
		void asyncReceiveHandle();

		// Asynchronous message receive handle
		virtual void onAsyncReceive(int byteCount) = 0;
		// Asynchronous receive error handle
		virtual void onAsyncReceiveError() = 0;
		// Asynchronous shutdown handle
		virtual void onAsyncShutdown() = 0;
		// Asynchronous send error handle
		virtual void onAsyncSendError(int byteCount) = 0;
	 public:
		// Creates a new socket session
		TcpSessionSocket(
			Socket socket,
			const Endpoint& endpoint,
			size_t receiveBufferSize = 8192);
		// Deleted copy constructor
		TcpSessionSocket(const TcpSessionSocket& server) = delete;
		// Closes and destroys session
		virtual ~TcpSessionSocket() = default;

		// Returns client TCP socket
		const Socket& getSocket() const noexcept;
		// Returns client TCP socket remote endpoint
		const Endpoint& getEndpoint() const noexcept;
		// Returns true if session is still running
		bool isRunning() const noexcept;
		// Returns message receive buffer
		const std::vector<uint8_t>& getReceiveBuffer() const noexcept;
		// Returns message send buffer
		const std::vector<uint8_t>& getSendBuffer() const noexcept;

		// Returns sent datagram byte count
		void send(const Datagram& datagram);
	};
}
