#pragma once
#include "Injector/Network/Endpoint.hpp"
#include "Injector/Network/SocketProtocol.hpp"
#include "Injector/Network/SocketShutdown.hpp"
#include "Injector/Network/RequestResponse.hpp"

namespace Injector
{
	class Socket final
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
		// Moves other socket
		Socket(Socket&& socket) noexcept;
		// Deleted copy constructor
		Socket(const Socket& socket) = delete;
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
		bool accept(Socket& socket, Endpoint& endpoint) noexcept;
		// Returns true if connected to remote endpoint
		bool connect(const Endpoint& endpoint) noexcept;

		// Returns receives message byte count
		int receive(void* buffer, size_t size) noexcept;
		// Returns sended message byte count
		int send(const void* buffer, size_t size) noexcept;

		// Returns receives message byte count
		template<class T = uint8_t>
		int receive(std::vector<T>& buffer)
		{
			return receive(
				buffer.data(),
				buffer.size() * sizeof(T));
		}
		// Returns sended message byte count
		template<class T = uint8_t>
		int send(const std::vector<T>& buffer)
		{
			return send(
				buffer.data(),
				buffer.size() * sizeof(T));
		}

		// Returns receives message byte count
		int receiveFrom(
			void* buffer,
			size_t size,
			Endpoint& endpoint) noexcept;
		// Returns sended message byte count
		int sendTo(
			const void* buffer,
			size_t size,
			const Endpoint& endpoint) noexcept;

		// Returns receives message byte count
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
		// Returns sended message byte count
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
		bool shutdown(SocketShutdown shutdown) noexcept;
		// Closes socket connection and releases all resources
		bool close() noexcept;

		// Returns true if sockets is equal
		bool operator==(const Socket& socket) const noexcept;
		// Returns true if sockets is not equal
		bool operator!=(const Socket& socket) const noexcept;

		// Socket move assigment operator
		Socket& operator=(Socket&& socket) noexcept;

		// Returns true if a < b
		static bool less(
			const Socket& a,
			const Socket& b) noexcept;
	};
}
