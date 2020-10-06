#pragma once
#include "Injector/ECS/System.hpp"
#include "Injector/Network/Socket.hpp"
#include "Injector/Network/SocketConnect.hpp"

namespace Injector
{
	class TcpClientSystem : public System
	{
	 protected:
		// Client TCP socket
		Socket socket;
		// Socket connect state
		SocketConnect socketConnect;
		// Server response timeout time
		double timeoutTime;
		// Last server response time
		double lastResponseTime;
		// Message receive buffer
		std::vector<uint8_t> receiveBuffer;

		// Socket result handle
		virtual void onConnect(bool result);
		// Message receive handle
		virtual void onReceive(int count);
		// Response timeout handle
		virtual void onResponseTimeout();
	 public:
		// Creates and binds a new TCP client system
		explicit TcpClientSystem(
			SocketFamily family,
			double timeoutTime = 6.0,
			size_t receiveBufferSize = 65536);

		// Returns client socket
		const Socket& getSocket() const noexcept;
		// Returns client socket connect state
		SocketConnect getSocketConnect() const noexcept;
		// Returns server response timeout time
		double getTimeoutTime() const noexcept;
		// Returns last server response time
		double getLastResponseTime() const noexcept;
		// Returns message receive buffer
		const std::vector<uint8_t>& getReceiveBuffer() const noexcept;

		// Executes on each update cycle
		void update() override;

		// Starts connection to the server
		void connect(const Endpoint& endpoint);
	};
}
