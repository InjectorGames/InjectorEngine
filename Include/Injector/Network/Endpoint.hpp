#pragma once
#include "Injector/Defines.hpp"
#include "Injector/Network/SocketProtocol.hpp"
#include "Injector/Network/SocketFamily.hpp"

#include <string>
#include <vector>

#if INJECTOR_SYSTEM_LINUX || INJECTOR_SYSTEM_MACOS
#include <netdb.h>
#include <sys/socket.h>
#elif INJECTOR_SYSTEM_WINDOWS
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#error Unknown operating system
#endif

namespace Injector
{
	// Socket IP address and port number storage
	struct Endpoint
	{
	 private:
		// Endpoint socket address storage
		sockaddr_storage storage;
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
		// Destroys endpoint
		virtual ~Endpoint() = default;

		// Returns endpoint socket address storage
		sockaddr_storage& getStorage() noexcept;
		// Returns endpoint socket address storage
		const sockaddr_storage& getStorage() const noexcept;

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

		static bool less(
			const Endpoint& a,
			const Endpoint& b);

		struct Less
		{
			bool operator()(
				const Endpoint& a,
				const Endpoint& b) const
			{
				return less(a, b);
			}
		};
	};
}
