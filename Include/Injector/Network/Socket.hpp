#pragma once
#include "Injector/Network/Endpoint.hpp"
#include "Injector/Network/SocketProtocol.hpp"
#include "Injector/Network/SocketShutdown.hpp"

namespace Injector
{
	class Socket
	{
	 protected:
		SocketFamily family;
		SocketProtocol protocol;
		int handle;
	 public:
		// Creates a new null socket
		Socket() noexcept;
		// Creates a new socket
		Socket(
			SocketFamily family,
			SocketProtocol protocol);
		// Shutdowns, closes and destroys socket
		virtual ~Socket();

		// Returns socket address family
		SocketFamily getAddressFamily() const noexcept;
		// Returns socket protocol type
		SocketProtocol getProtocolType() const noexcept;

		// Returns true if socket is listening
		bool getIsListening() const;

		// Returns current endpoint to which socket is bound
		Endpoint getLocalEndpoint() const;
		// Returns endpoint of connected socked
		Endpoint getRemoteEndpoint() const;

		// Sets socket blocking mode
		void setBlocking(bool blocking) const;

		// Assigns socket local endpoint
		void bind(const Endpoint& endpoint);
		// Listens for connections on socket
		void listen();

		// Returns true if connection has been accepted
		bool accept(
			Endpoint& endpoint,
			Socket& socket) noexcept;
		// Returns true if connected to remote endpoint
		bool connect(const Endpoint& endpoint) noexcept;

		// Receives message from connected endpoint
		int receive(
			void* buffer,
			size_t size) noexcept;
		// Sends message to connected endpoint
		int send(
			const void* buffer,
			size_t size) noexcept;

		// Receives message from connected endpoint
		template<class T = uint8_t>
		int receive(std::vector<T>& buffer)
		{
			return receive(
				buffer.data(),
				buffer.size() * sizeof(T));
		}
		// Sends message to connected endpoint
		template<class T = uint8_t>
		int send(const std::vector<T>& buffer)
		{
			return send(
				buffer.data(),
				buffer.size() * sizeof(T));
		}

		// Receives message from specified endpoint
		int receiveFrom(
			void* buffer,
			size_t size,
			Endpoint& endpoint) noexcept;
		// Sends message to specified endpoint
		int sendTo(
			const void* buffer,
			size_t size,
			const Endpoint& endpoint) noexcept;

		// Receives message from specified endpoint
		template<class T = uint8_t>
		int receiveFrom(
			std::vector<T>& buffer,
			Endpoint& endpoint)
		{
			return receiveFrom(
				buffer.data(),
				buffer.size() * sizeof(T),
				endpoint);
		}
		// Sends message to specified endpoint
		template<class T = uint8_t>
		int sendTo(
			const std::vector<T>& buffer,
			const Endpoint& endpoint)
		{
			return sendTo(
				buffer.data(),
				buffer.size() * sizeof(T),
				endpoint);
		}

		// Shutdowns part of a full-duplex connection
		// Read: shutdowns socket sending
		// Write: shutdowns socket receiving
		// Both: shutdowns sending and receiving
		void shutdown(SocketShutdown shutdown);
		// Closes socket connection and releases all resources
		void close();
	};
}
