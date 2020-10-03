#pragma once
#include "Injector/Network/SocketType.hpp"
#include "Injector/Network/AddressFamily.hpp"

#include <string>
#include <vector>

namespace Injector
{
	// Socket IP address and port number storage
	struct Endpoint final
	{
	 protected:
		// Endpoint sockaddr_storage pointer
		void* handle;
	 public:
		// Any IPv4 IP address
		inline static const std::string ipv4Any = "0.0.0.0";
		// Any IPv6 IP address
		inline static const std::string ipv6Any = "::";
		// Loopback IPv4 IP address
		inline static const std::string ipv4Loopback = "127.0.0.1";
		// loopback IPv6 IP address
		inline static const std::string ipv6Loopback = "::1";

		// Creates a new empty endpoint
		Endpoint() noexcept;
		// Copies other endpoint
		Endpoint(const Endpoint& endpoint) noexcept;
		// Destroys endpoint
		virtual ~Endpoint();

		// Returns endpoint sockaddr_storage pointer
		void* getHandle() const noexcept;

		// Returns endpoint socket address family on success
		bool getAddressFamily(AddressFamily& addressFamily) const noexcept;
		// Returns endpoint IPv6 scope identifier on success
		bool getScopeID(uint32_t& scopeID) const noexcept;

		// Returns endpoint IP address on success
		bool getAddress(std::string& address) const noexcept;
		// Returns endpoint IP address on success
		bool getAddress(std::vector<uint8_t>& address) const noexcept;

		// Returns endpoint port number on success
		bool getPort(std::string& port) const noexcept;
		// Returns endpoint port number on success
		bool getPort(uint16_t& port) const noexcept;

		// Returns endpoint IP address and port number on success
		bool getAddressAndPort(
			std::string& address,
			std::string& port) const noexcept;

		// Returns true if endpoints is equal
		bool operator==(const Endpoint& vector) const noexcept;
		// Returns true if endpoints is not equal
		bool operator!=(const Endpoint& vector) const noexcept;

		// Resolves endpoints from host and service on success
		static bool resolve(
			AddressFamily addressFamily,
			SocketType socketType,
			const std::string& host,
			const std::string& service,
			std::vector<Endpoint>& endpoint) noexcept;
		// Resolves host and service from endpoint on success
		static bool resolve(
			const Endpoint& endpoint,
			std::string& host,
			std::string& service) noexcept;

		// Creates a new endpoint on success
		static bool create(
			const std::string& address,
			const std::string& port,
			Endpoint& endpoint) noexcept;

		// Returns true if a < b
		static bool less(
			const Endpoint& a,
			const Endpoint& b) noexcept;
	};
}
