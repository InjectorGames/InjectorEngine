#pragma once
#include "Injector/Network/Socket.hpp"
#include "Injector/Network/Datagram.hpp"
#include "Injector/Network/SocketConnect.hpp"

#include <thread>
#include <mutex>

namespace Injector
{
	// Transfer Control Protocol client class
	class TcpClient
	{
	 protected:
		// Client TCP socket
		Socket socket;
		// Socket connect state
		SocketConnect socketConnect;
		// Server response timeout time
		double responseTimeoutTime;
		// Last server response time
		double lastResponseTime;
		// Message receive buffer
		std::vector<uint8_t> receiveBuffer;
		// Message send buffer
		std::vector<uint8_t> sendBuffer;
	 public:
		// Creates and binds a new TCP client
		explicit TcpClient(
			SocketFamily family,
			double responseTimeoutTime = 6.0,
			size_t receiveBufferSize = 8192);

		// Returns client TCP socket
		const Socket& getSocket() const noexcept;
		// Returns client TCP socket connect state
		SocketConnect getSocketConnect() const noexcept;
		// Returns server response timeout time
		double getTimeoutTime() const noexcept;
		// Returns last server response time
		double getLastResponseTime() const noexcept;
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