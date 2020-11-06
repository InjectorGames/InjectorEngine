#pragma once
#include "Injector/Network/Socket.hpp"
#include "Injector/Network/Datagram.hpp"

#include <thread>
#include <atomic>

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
		// Message receive thread
		std::thread receiveThread;
		// Is receive thread is still running
		std::atomic<bool> receiveRunning;
		// Message receive buffer
		std::vector<uint8_t> receiveBuffer;
		// Message send buffer
		std::vector<uint8_t> sendBuffer;

		// Asynchronous message receive handle
		void asyncReceiveHandle();

		// Returns sent datagram byte count
		void asyncSend(const Datagram& datagram);

		// Asynchronous message receive handle
		virtual bool onAsyncReceive(int byteCount) = 0;
		// Asynchronous receive error handle
		virtual void onAsyncReceiveError() = 0;
		// Asynchronous shutdown handle
		virtual void onAsyncShutdown() = 0;
		// Asynchronous send error handle
		virtual void onAsyncSendError(int byteCount) = 0;
	 public:
		// Creates a new TCP session socket
		TcpSessionSocket(
			Socket socket,
			const Endpoint& endpoint,
			size_t receiveBufferSize = 8192);
		// Deleted copy constructor
		TcpSessionSocket(const TcpSessionSocket& server) = delete;
		// Closes and destroys TCP session socket
		virtual ~TcpSessionSocket();

		// Returns client TCP socket
		const Socket& getSocket() const noexcept;
		// Returns client TCP socket remote endpoint
		const Endpoint& getEndpoint() const noexcept;
		// Returns session receive thread
		const std::thread& getReceiveThread() const noexcept;
		// Returns session receive running atomic
		const std::atomic<bool>& getReceiveRunning() const noexcept;
		// Returns message receive buffer
		const std::vector<uint8_t>& getReceiveBuffer() const noexcept;
		// Returns message send buffer
		const std::vector<uint8_t>& getSendBuffer() const noexcept;
	};
}
