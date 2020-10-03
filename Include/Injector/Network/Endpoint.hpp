#pragma once
#include "Injector/Network/SocketFamily.hpp"

#include <string>
#include <vector>

namespace Injector
{
	class Endpoint
	{
	 public:
		void* handle;
	 public:
		inline static const std::string ipv4Any = "0.0.0.0";
		inline static const std::string ipv6Any = "::";
		inline static const std::string ipv4Loopback = "127.0.0.1";
		inline static const std::string ipv6Loopback = "::1";

		Endpoint();
		Endpoint(Endpoint& endpoint);
		Endpoint(Endpoint&& endpoint) noexcept;
		virtual ~Endpoint();

		bool isValid() const noexcept;

		bool getFamily(SocketFamily& family) const noexcept;

		bool getAddress(std::string& address) const noexcept;
		bool getAddress(std::vector<uint8_t>& address) const noexcept;

		bool getPort(std::string& port) const noexcept;
		bool getPort(uint16_t& port) const noexcept;

		bool getAddressAndPort(
			std::string& address,
			std::string& port) const noexcept;

		bool operator==(const Endpoint& vector) const noexcept;
		bool operator!=(const Endpoint& vector) const noexcept;

		static Endpoint create(
			const std::string& address,
			const std::string& port);
		static bool create(
			const std::string& address,
			const std::string& port,
			Endpoint& endpoint) noexcept;

		static std::vector<Endpoint> resolve(
			const std::string& host,
			const std::string& service);
		static bool resolve(
			const std::string& host,
			const std::string& service,
			std::vector<Endpoint>& endpoint) noexcept;

		static bool resolve(
			const Endpoint& endpoint,
			std::string& host,
			std::string& service) noexcept;

		static bool less(
			const Endpoint& a,
			const Endpoint& b) noexcept;
	};
}
