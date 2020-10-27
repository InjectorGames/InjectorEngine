#pragma once
#include "Injector/Network/Socket.hpp"

namespace Injector
{
	// Transfer Control Protocol server session class
	class TcpServerSession
	{
	 protected:
		// Is session still alive
		bool alive;
		// Session timeout time
		double timeoutTime;
		// Last socket response time
		double lastResponseTime;
		// Session socket
		Socket socket;
		// Socket remote endpoint
		Endpoint endpoint;
		// Message receive buffer
		std::vector<uint8_t> receiveBuffer;
		// Message send buffer
		std::vector<uint8_t> sendBuffer;

		// Message receive handle
		virtual void onReceive(size_t byteCount);
		// Request timeout handle
		virtual void onRequestTimeout();
	 public:
		// Creates a new socket session
		TcpServerSession(
			Socket socket,
			const Endpoint& endpoint,
			bool alive = true,
			double timeoutTime = 6.0,
			size_t receiveBufferSize = 8192,
			size_t sendBufferSize = 8192);

		// Closes and destroys session
		virtual ~TcpServerSession();

		// Returns true if session is still alive
		bool isAlive() const noexcept;
		// Returns client timeout time
		double getTimeoutTime() const noexcept;
		// Returns client last response time
		double getLastResponseTime() const noexcept;
		// Returns client TCP socket
		const Socket& getSocket() const noexcept;
		// Returns client TCP socket remote endpoint
		const Endpoint& getEndpoint() const noexcept;
		// Returns message receive buffer
		const std::vector<uint8_t>& getReceiveBuffer() const noexcept;
		// Returns message send buffer
		const std::vector<uint8_t>& getSendBuffer() const noexcept;

		// Executes on each update cycle
		void update();
	};
}
