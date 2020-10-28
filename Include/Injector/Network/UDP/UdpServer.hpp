#pragma once
#include "Injector/Network/Socket.hpp"
#include "Injector/Network/Datagram.hpp"

#include <thread>
#include <mutex>

namespace Injector
{
	// User Datagram Protocol server class
	class UdpServer
	{
	 protected:
		// Server TCP socket
		Socket socket;
		// Is server still running
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
			int byteCount) = 0;
	 public:
		// Creates and binds a new UDP server
		UdpServer(
			SocketFamily family,
			const std::string& port,
			size_t receiveBufferSize = 8192);
		// Deleted copy constructor
		UdpServer(const UdpServer& server) = delete;

		// Returns server TCP socket
		const Socket& getSocket() const noexcept;
		// Returns true if server is still running
		bool isRunning() const noexcept;

		// Starts server receive
		void start();

		// Returns sent datagram byte count
		int sendTo(
			const Datagram& datagram,
			const Endpoint& endpoint);
	};
}
