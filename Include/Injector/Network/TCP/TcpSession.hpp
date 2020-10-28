#pragma once
#include "Injector/Network/Socket.hpp"
#include "Injector/Network/Datagram.hpp"

#include <thread>

namespace Injector
{
	// Transfer Control Protocol session class
	class TcpSession
	{
	 protected:
		// Client socket
		Socket socket;
		// Client remote endpoint
		Endpoint endpoint;
		// Last client request time
		double lastRequestTime;
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

		// Message receive handle
		virtual void onAsyncReceive(
			int byteCount);
	 public:
		// Creates a new socket session
		TcpSession(
			Socket socket,
			const Endpoint& endpoint,
			size_t receiveBufferSize = 8192);
		// Deleted copy constructor
		TcpSession(const TcpSession& server) = delete;
		// Closes and destroys session
		virtual ~TcpSession() = default;

		// Returns client TCP socket
		const Socket& getSocket() const noexcept;
		// Returns client TCP socket remote endpoint
		const Endpoint& getEndpoint() const noexcept;
		// Returns client last request time
		double getLastRequestTime() const noexcept;
		// Returns true if session is still running
		bool isRunning() const noexcept;
		// Returns message receive buffer
		const std::vector<uint8_t>& getReceiveBuffer() const noexcept;
		// Returns message send buffer
		const std::vector<uint8_t>& getSendBuffer() const noexcept;

		// Returns sent datagram byte count
		int send(const Datagram& datagram);
	};
}
