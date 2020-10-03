#pragma once
#include "Injector/Network/Endpoint.hpp"
#include "Injector/Network/SocketType.hpp"
#include "Injector/Network/SocketShutdown.hpp"

namespace Injector
{
	class Socket
	{
	 protected:
		uint64_t handle;
	 public:
		// Creates a new empty socket
		Socket() noexcept;
		// Closes and destroys socket
		virtual ~Socket();

		// Returns true if socket is not null
		bool isValid() noexcept;

		// Returns true if socket is listening on success
		bool getIsListening(bool& listening) noexcept;
		// Returns socket type on success
		bool getSocketType(SocketType& socketType) noexcept;

		// TODO: add other options

		// Returns current endpoint to which socket is bound on success
		bool getLocalEndpoint(
			Endpoint& endpoint) noexcept;
		// Returns endpoint of connected socked on success
		bool getRemoteEndpoint(
			Endpoint& endpoint) noexcept;

		// Assigns socket local endpoint on success
		bool bind(const Endpoint& endpoint) noexcept;
		// Connects socket to remote endpoint on success
		bool connect(const Endpoint& endpoint) noexcept;

		// Listens for connections on socket on success
		bool listen() noexcept;
		// Accepts connection on socket on success
		bool accept(
			Endpoint& endpoint,
			Socket& socket) noexcept;

		// Receives message from connected endpoint
		int receive(
			void* buffer,
			size_t size) noexcept;
		// Sends message to connected endpoint
		int send(
			const void* buffer,
			size_t size) noexcept;

		// Receives message from specified endpoint
		int receiveFrom(
			void* buffer,
			size_t size,
			Endpoint& endpoint) noexcept;
		// Sends message to specified endpoint
		int sendTo(
			void* buffer,
			size_t size,
			const Endpoint& endpoint) noexcept;

		// Shutdowns part of a full-duplex connection
		// Read: shutdowns socket sending
		// Write: shutdowns socket receiving
		// Both: shutdowns sending and receiving
		bool shutdown(
			SocketShutdown shutdown) noexcept;
		// Closes socket connection and releases all resources
		bool close() noexcept;

		// Creates a new socket on success
		static bool create(
			AddressFamily family,
			SocketType type,
			Socket& socket) noexcept;
	};
}
