#pragma once
#include "Injector/Network/Socket.hpp"
#include "Injector/Network/Datagram.hpp"

#include <thread>

namespace Injector
{
	// Client socket class
	class ClientSocket
	{
	 protected:
		// Client socket
		Socket socket;
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

		// Asynchronous connect error handle
		virtual void onAsyncConnectError() = 0;
		// Asynchronous message receive handle
		virtual void onAsyncReceive(int byteCount) = 0;
		// Asynchronous receive error handle
		virtual void onAsyncReceiveError() = 0;
		// Asynchronous shutdown handle
		virtual void onAsyncShutdown() = 0;
		// Asynchronous send error handle
		virtual void onAsyncSendError(int byteCount) = 0;
	 public:
		// Creates and binds a new socket client
		explicit ClientSocket(
			SocketFamily family,
			SocketProtocol protocol,
			size_t receiveBufferSize = 8192);
		// Deleted copy constructor
		ClientSocket(const ClientSocket& server) = delete;

		// Returns client socket
		Socket& getSocket() noexcept;
		// Returns client socket
		const Socket& getSocket() const noexcept;

		// Returns true if client is still running
		bool isRunning() const noexcept;
		// Returns message receive buffer
		const std::vector<uint8_t>& getReceiveBuffer() const noexcept;
		// Returns message send buffer
		const std::vector<uint8_t>& getSendBuffer() const noexcept;

		// Starts connection to the server
		void connect(const Endpoint& endpoint);

		// Returns sent datagram byte count
		void send(const Datagram& datagram);
		// Returns sent datagram byte count
		void sendTo(
			const Datagram& datagram,
			const Endpoint& endpoint);
	};
}