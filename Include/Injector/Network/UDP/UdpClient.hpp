#pragma once
#include "Injector/Network/Socket.hpp"
#include "Injector/Network/Datagram.hpp"

#include <thread>

namespace Injector
{
	// User Datagram Protocol client class
	class UdpClient
	{
	 protected:
		// Client TCP socket
		Socket socket;
		// Last server response time
		double lastResponseTime;
		// Is client still running
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
		virtual void onAsyncReceive(
			int byteCount);
	 public:
		// Creates and binds a new UDP client
		explicit UdpClient(
			SocketFamily family,
			size_t receiveBufferSize = 8192);
		// Deleted copy constructor
		UdpClient(const UdpClient& server) = delete;

		// Returns client UDP socket
		const Socket& getSocket() const noexcept;
		// Returns last client response time
		double getLastResponseTime() const noexcept;
		// Returns true if client is still running
		bool isRunning() const noexcept;
		// Returns message receive buffer
		const std::vector<uint8_t>& getReceiveBuffer() const noexcept;
		// Returns message send buffer
		const std::vector<uint8_t>& getSendBuffer() const noexcept;

		// Connects client to the server
		void connect(const Endpoint& endpoint);
		// Returns sent datagram byte count
		int send(const Datagram& datagram);
	};
}
