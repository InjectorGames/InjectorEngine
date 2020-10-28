#pragma once
#include "Injector/Network/Socket.hpp"
#include "Injector/Network/Datagram.hpp"

#include <thread>

namespace Injector
{
	// Transfer Control Protocol client class
	class TcpClient
	{
	 protected:
		// Client TCP socket
		Socket socket;
		// Last server response time
		double lastResponseTime;
		// Is client is still running
		bool running;
		// Message receive thread
		std::thread receiveThread;
		// Message receive buffer
		std::vector<uint8_t> receiveBuffer;
		// Message send buffer
		std::vector<uint8_t> sendBuffer;

		// Asynchronous message receive handle
		void asyncReceiveHandle(
			const Endpoint& endpoint);

		// Asynchronous message receive handle
		virtual void onAsyncReceive(
			int byteCount);
	 public:
		// Creates and binds a new TCP client
		explicit TcpClient(
			SocketFamily family,
			size_t receiveBufferSize = 8192);

		// Returns client TCP socket
		const Socket& getSocket() const noexcept;
		// Returns last client response time
		double getLastResponseTime() const noexcept;
		// Returns true if client is still running
		bool isRunning() const noexcept;
		// Returns message receive buffer
		const std::vector<uint8_t>& getReceiveBuffer() const noexcept;
		// Returns message send buffer
		const std::vector<uint8_t>& getSendBuffer() const noexcept;

		// Starts connection to the server
		void connect(const Endpoint& endpoint);
		// Returns sent datagram byte count
		int send(const Datagram& datagram);
	};
}