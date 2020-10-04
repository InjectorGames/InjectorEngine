#pragma once
#include "Injector/System.hpp"
#include "Injector/Network/Socket.hpp"
#include "Injector/Network/TcpSocketConnect.hpp"

namespace Injector
{
	class TcpClientSystem : public System
	{
	 protected:
		// TCP client socket
		Socket tcpSocket;
		// Is TCP client connected to server
		bool connected;
	 public:
		// Creates and binds a new TCP client system
		explicit TcpClientSystem(SocketFamily family);

		void update() override;

		// Starts async connect to remote endpoint
		void connect(
			const Endpoint& endpoint) noexcept;
	};
}
