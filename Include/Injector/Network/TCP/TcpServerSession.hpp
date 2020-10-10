#pragma once
#include "Injector/Network/Socket.hpp"

namespace Injector
{
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
			size_t receiveBufferSize = 65536,
			size_t sendBufferSize = 65536);

		// Closes and destroys session
		virtual ~TcpServerSession();

		// Returns true if session is still alive
		bool isAlive() const noexcept;
		// Returns session timeout time
		double getTimeoutTime() const noexcept;
		// Returns last socket response time
		double getLastResponseTime() const noexcept;
		// Returns session TCP socket
		const Socket& getSocket() const noexcept;
		// Returns session socket remote endpoint
		const Endpoint& getEndpoint() const noexcept;
		// Returns socket message receive buffer
		const std::vector<uint8_t>& getReceiveBuffer() const noexcept;

		// Executes on each update cycle
		void update();
	};
}
