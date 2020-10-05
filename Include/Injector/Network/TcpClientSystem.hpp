#pragma once
#include "Injector/System.hpp"
#include "Injector/Network/Socket.hpp"
#include "Injector/Network/SocketConnect.hpp"

namespace Injector
{
	class TcpClientSystem : public System
	{
	 protected:
		// TCP socket
		Socket tcpSocket;
		// Socket connect state
		SocketConnect socketConnect;
		// Server response timeout time
		double timeoutTime;
		// Last server response time
		double lastResponseTime;
		// Message receive buffer
		std::vector<uint8_t> receiveBuffer;

		// Connection result handle
		virtual void onConnect(bool result) = 0;
		// On message receive handle
		virtual void onReceive(int count) = 0;
		// On disconnect handle
		virtual void onDisconnect() = 0;
	 public:
		// Creates and binds a new TCP client system
		explicit TcpClientSystem(
			SocketFamily family,
			double timeoutTime = 6.0,
			size_t receiveBufferSize = 0xFF);

		void update() override;

		// Starts connection to server
		void connect(const Endpoint& endpoint);
	};
}
