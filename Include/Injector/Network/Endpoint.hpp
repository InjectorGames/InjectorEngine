#pragma once
#include "Injector/Network/SocketProtocol.hpp"
#include "Injector/Network/SocketFamily.hpp"

#include <string>
#include <vector>

namespace Injector
{
	// Socket IP address and port number storage
	struct Endpoint final
	{
	 private:
		// Endpoint sockaddr_storage pointer
		void* handle;
	 public:
		// Any IPv4 IP address ("0.0.0.0")
		static const std::string anyAddressIPv4;
		// Any IPv6 IP address ("::")
		static const std::string anyAddressIPv6;
		// Loopback IPv4 IP address ("127.0.0.1")
		static const std::string loopbackAddressIPv4;
		// Loopback IPv6 IP address ("::1")
		static const std::string loopbackAddressIPv6;
		// Any port number ("0")
		static const std::string anyPortNumber;
		// IPv4 address binary size (4 bytes)
		static const size_t addressSizeIPv4;
		// IPv4 address binary size (16 bytes)
		static const size_t addressSizeIPv6;
		// Any IPv4 IP address and port number endpoint
		static const Endpoint anyIPv4;
		// Any IPv6 IP address and port number endpoint
		static const Endpoint anyIPv6;

		// Creates a new empty endpoint
		Endpoint() noexcept;
		// Creates a new IPv4/IPv6 socket endpoint
		Endpoint(
			const std::string& address,
			const std::string& port);
		// Creates a new IPv4 socket endpoint
		Endpoint(
			const std::vector<uint8_t>& address,
			uint16_t port);
		// Creates a new IPv6 socket endpoint
		Endpoint(
			const std::vector<uint8_t>& address,
			uint16_t port,
			uint32_t scopeID,
			uint32_t flowInfo);
		// Copies other endpoint
		Endpoint(const Endpoint& endpoint) noexcept;
		// Moves other endpoint
		Endpoint(Endpoint&& endpoint) noexcept;
		// Destroys endpoint
		virtual ~Endpoint();

		// Returns endpoint sockaddr_storage pointer
		void* getHandle() const noexcept;
		// Returns socket endpoint family
		SocketFamily getSocketFamily() const noexcept;

		// Returns socket endpoint IP address
		std::vector<uint8_t> getAddress() const;
		// Returns socket endpoint port number
		uint16_t getPort() const;

		// Returns endpoint socket IP address string
		std::string getAddressString() const;
		// Returns endpoint socket port number string
		std::string getPortString() const;

		// Returns endpoint socket IP address and port number strings
		void getAddressAndPortString(
			std::string& address,
			std::string& port) const;

		// Returns endpoint IPv6 scope identifier
		uint32_t getScopeID() const;
		// Returns endpoint IPv6 flow information
		uint32_t getFlowInfo() const;

		// Returns true if socket endpoints is equal
		bool operator==(const Endpoint& endpoint) const noexcept;
		// Returns true if socket endpoints is not equal
		bool operator!=(const Endpoint& endpoint) const noexcept;

		// Endpoint copy assigment operator
		Endpoint& operator=(const Endpoint& endpoint) noexcept;
		// Endpoint move assigment operator
		Endpoint& operator=(Endpoint&& endpoint) noexcept;

		// Resolves socket endpoints from host and service
		static std::vector<Endpoint> resolve(
			SocketFamily family,
			SocketProtocol protocol,
			const std::string& host,
			const std::string& service);
		// Resolves host and service from socket endpoint
		static void resolve(
			const Endpoint& endpoint,
			std::string& host,
			std::string& service);

		// Returns true if a < b
		static bool less(
			const Endpoint& a,
			const Endpoint& b) noexcept;
	};
}
