#pragma once
#include "Injector/ECS/EcsSystem.hpp"
#include "Injector/Network/Socket.hpp"

namespace Injector
{
	// User Datagram Protocol client ECS system class
	class UdpClientEcsSystem : public EcsSystem
	{
	 protected:
		// Client UDP socket
		Socket socket;
		// Is client still connected to the server
		bool isConnected;
		// Server response timeout time
		double timeoutTime;
		// Last server response time
		double lastResponseTime;
		// Datagram receive buffer
		std::vector<uint8_t> receiveBuffer;
		// Datagram send buffer
		std::vector<uint8_t> sendBuffer;

		// Message receive handle
		virtual void onReceive(size_t byteCount);
		// Response timeout handle
		virtual void onResponseTimeout();
	 public:
		// Creates and binds a new UDP client ECS system
		explicit UdpClientEcsSystem(
			SocketFamily family,
			double timeoutTime = 6.0,
			size_t receiveBufferSize = 8192,
			size_t sendBufferSize = 8192);

		// Returns client UDP socket
		const Socket& getSocket() const noexcept;
		// Returns server response timeout time
		double getTimeoutTime() const noexcept;
		// Returns last server response time
		double getLastResponseTime() const noexcept;
		// Returns message receive buffer
		const std::vector<uint8_t>& getReceiveBuffer() const noexcept;
		// Returns message send buffer
		const std::vector<uint8_t>& getSendBuffer() const noexcept;

		// Executes on each update cycle
		void update() override;

		// Starts connection to the server
		void connect(const Endpoint& endpoint);
	};
}
