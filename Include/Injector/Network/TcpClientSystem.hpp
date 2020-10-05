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
	 public:
		// Creates and binds a new TCP client system
		explicit TcpClientSystem(
			SocketFamily family,
			double connectTimeout = 3.0);

		void update() override;

		// Starts connection to server
		void connect(const Endpoint& endpoint);
	};
}
