#include "Injector/Network/Endpoint.hpp"
#include "Injector/Engine.hpp"
#include "Injector/Exception/Exception.hpp"

#include <cstring>

namespace Injector
{
	const std::string Endpoint::anyAddressIPv4 = "0.0.0.0";
	const std::string Endpoint::anyAddressIPv6 = "::";
	const std::string Endpoint::loopbackAddressIPv4 = "127.0.0.1";
	const std::string Endpoint::loopbackAddressIPv6 = "::1";
	const std::string Endpoint::anyPortNumber = "0";
	const size_t Endpoint::addressSizeIPv4 = sizeof(in_addr);
	const size_t Endpoint::addressSizeIPv6 = sizeof(in6_addr);
	const Endpoint Endpoint::anyIPv4 = Endpoint(anyAddressIPv4, anyPortNumber);
	const Endpoint Endpoint::anyIPv6 = Endpoint(anyAddressIPv6, anyPortNumber);

	Endpoint::Endpoint() noexcept
	{
		memset(
			&storage,
			0,
			sizeof(sockaddr_storage));
	}
	Endpoint::Endpoint(
		const std::string& address,
		const std::string& port)
	{
		auto hints = addrinfo();

		memset(
			&hints,
			0,
			sizeof(addrinfo));

		hints.ai_flags =
			AI_NUMERICHOST |
			AI_NUMERICSERV;

		addrinfo* addressInfos;

		auto result = getaddrinfo(
			address.c_str(),
			port.c_str(),
			&hints,
			&addressInfos);

		if (result != 0)
		{
			freeaddrinfo(addressInfos);

			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to get address information");
		}

		memset(
			&storage,
			0,
			sizeof(sockaddr_storage));

		memcpy(
			&storage,
			addressInfos->ai_addr,
			addressInfos->ai_addrlen);

		freeaddrinfo(addressInfos);
	}
	Endpoint::Endpoint(
		const std::vector<uint8_t>& address,
		uint16_t port)
	{
		if (address.size() != sizeof(in_addr))
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Incorrect address size");
		}

		memset(
			&storage,
			0,
			sizeof(sockaddr_storage));

		auto socketAddress =
			reinterpret_cast<sockaddr_in*>(&storage);

		socketAddress->sin_family = AF_INET;

		memcpy(
			&socketAddress->sin_addr,
			address.data(),
			sizeof(in_addr));

		socketAddress->sin_port = port;
	}
	Endpoint::Endpoint(
		const std::vector<uint8_t>& address,
		uint16_t port,
		uint32_t scopeID,
		uint32_t flowInfo)
	{
		if (address.size() != sizeof(in6_addr))
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Incorrect address size");
		}

		memset(
			&storage,
			0,
			sizeof(sockaddr_storage));

		auto socketAddress =
			reinterpret_cast<sockaddr_in6*>(&storage);

		socketAddress->sin6_family = AF_INET6;
		socketAddress->sin6_scope_id = scopeID;
		socketAddress->sin6_flowinfo = flowInfo;

		memcpy(
			&socketAddress->sin6_addr,
			address.data(),
			sizeof(in6_addr));

		socketAddress->sin6_port = port;
	}

	sockaddr_storage& Endpoint::getStorage() noexcept
	{
		return storage;
	}
	const sockaddr_storage& Endpoint::getStorage() const noexcept
	{
		return storage;
	}

	SocketFamily Endpoint::getSocketFamily() const noexcept
	{
		if (storage.ss_family == AF_INET)
			return SocketFamily::IPv4;
		else if (storage.ss_family == AF_INET6)
			return SocketFamily::IPv6;
		else
			return SocketFamily::Unspecified;
	}

	std::vector<uint8_t> Endpoint::getAddress() const
	{
		if (storage.ss_family == AF_INET)
		{
			auto address = std::vector<uint8_t>(sizeof(in_addr));

			auto socketAddress4 =
				reinterpret_cast<const sockaddr_in*>(&storage);

			memcpy(
				address.data(),
				&socketAddress4->sin_addr,
				sizeof(in_addr));

			return std::move(address);
		}
		else if (storage.ss_family == AF_INET6)
		{
			auto address = std::vector<uint8_t>(sizeof(in6_addr));

			auto socketAddress6 =
				reinterpret_cast<const sockaddr_in6*>(&storage);

			memcpy(
				address.data(),
				&socketAddress6->sin6_addr,
				sizeof(in6_addr));

			return std::move(address);
		}
		else
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Unspecified address family");
		}
	}
	uint16_t Endpoint::getPort() const
	{
		if (storage.ss_family == AF_INET)
		{
			auto socketAddress4 =
				reinterpret_cast<const sockaddr_in*>(&storage);
			return socketAddress4->sin_port;
		}
		else if (storage.ss_family == AF_INET6)
		{
			auto socketAddress6 =
				reinterpret_cast<const sockaddr_in6*>(&storage);
			return socketAddress6->sin6_port;
		}
		else
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Unspecified address family");
		}
	}

	std::string Endpoint::getAddressString() const
	{
		auto socketAddress =
			reinterpret_cast<const sockaddr*>(&storage);

		char addressString[NI_MAXHOST];

		auto flags =
			NI_NUMERICHOST;

		auto result = getnameinfo(
			socketAddress,
			sizeof(sockaddr_storage),
			addressString,
			NI_MAXHOST,
			nullptr,
			0,
			flags);

		if (result != 0)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to get name information");
		}

		return std::string(addressString);
	}
	std::string Endpoint::getPortString() const
	{
		auto socketAddress =
			reinterpret_cast<const sockaddr*>(&storage);

		char portString[NI_MAXSERV];

		auto flags =
			NI_NUMERICSERV;

		auto result = getnameinfo(
			socketAddress,
			sizeof(sockaddr_storage),
			nullptr,
			0,
			portString,
			NI_MAXSERV,
			flags);

		if (result != 0)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to get name information");
		}

		return std::string(portString);
	}

	void Endpoint::getAddressAndPortString(
		std::string& address,
		std::string& port) const
	{
		auto socketAddress =
			reinterpret_cast<const sockaddr*>(&storage);

		char addressString[NI_MAXHOST];
		char portString[NI_MAXSERV];

		auto flags =
			NI_NUMERICHOST |
			NI_NUMERICSERV;

		auto result = getnameinfo(
			socketAddress,
			sizeof(sockaddr_storage),
			addressString,
			NI_MAXHOST,
			portString,
			NI_MAXSERV,
			flags);

		if (result != 0)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to get name information");
		}

		address = std::string(addressString);
		port = std::string(portString);
	}

	uint32_t Endpoint::getScopeID() const
	{
		auto socketAddress =
			reinterpret_cast<const sockaddr_in6*>(&storage);

		if (socketAddress->sin6_family != AF_INET6)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Address family is not IPv6");
		}

		return socketAddress->sin6_scope_id;
	}
	uint32_t Endpoint::getFlowInfo() const
	{
		auto socketAddress =
			reinterpret_cast<const sockaddr_in6*>(&storage);

		if (socketAddress->sin6_family != AF_INET6)
		{
			{
				throw Exception(
					THIS_FUNCTION_NAME,
					"Address family is not IPv6");
			}
		}

		return socketAddress->sin6_flowinfo;
	}

	bool Endpoint::operator==(
		const Endpoint& endpoint) const noexcept
	{
		auto& otherStorage = endpoint.storage;

		if (storage.ss_family != otherStorage.ss_family)
			return false;

		if (storage.ss_family == AF_INET)
		{
			auto socketAddress4 =
				reinterpret_cast<const sockaddr_in*>(&storage);
			auto otherSocketAddress4 =
				reinterpret_cast<const sockaddr_in*>(&otherStorage);

			return
				socketAddress4->sin_port ==
					otherSocketAddress4->sin_port &&
				memcmp(&socketAddress4->sin_addr,
					&otherSocketAddress4->sin_addr,
					sizeof(in_addr)) == 0;
		}
		else if (storage.ss_family == AF_INET6)
		{
			auto socketAddress6 =
				reinterpret_cast<const sockaddr_in6*>(&storage);
			auto otherSocketAddress6 =
				reinterpret_cast<const sockaddr_in6*>(&otherStorage);

			return
				socketAddress6->sin6_port ==
					otherSocketAddress6->sin6_port &&
				socketAddress6->sin6_flowinfo ==
					otherSocketAddress6->sin6_flowinfo &&
				socketAddress6->sin6_scope_id ==
					otherSocketAddress6->sin6_scope_id &&
				memcmp(&socketAddress6->sin6_addr,
					&otherSocketAddress6->sin6_addr,
					sizeof(in6_addr)) == 0;
		}
		else
		{
			return false;
		}
	}
	bool Endpoint::operator!=(
		const Endpoint& endpoint) const noexcept
	{
		return !(*this == endpoint);
	}

	std::vector<Endpoint> Endpoint::resolve(
		SocketFamily family,
		SocketProtocol protocol,
		const std::string& host,
		const std::string& service)
	{
		if(!Engine::isNetworkInitialized())
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Network is not initialized");
		}

		auto hints = addrinfo();

		memset(
			&hints,
			0,
			sizeof(addrinfo));

		hints.ai_flags =
			AI_ADDRCONFIG |
			AI_V4MAPPED;

		if(family == SocketFamily::IPv4)
			hints.ai_family = AF_INET;
		else if(family == SocketFamily::IPv6)
			hints.ai_family = AF_INET6;

		if(protocol == SocketProtocol::TCP)
		{
			hints.ai_socktype = SOCK_STREAM;
			hints.ai_protocol = IPPROTO_TCP;
		}
		else if(protocol == SocketProtocol::UDP)
		{
			hints.ai_socktype = SOCK_DGRAM;
			hints.ai_protocol = IPPROTO_UDP;
		}

		addrinfo* addressInfos;

		auto result = getaddrinfo(
			host.c_str(),
			service.c_str(),
			&hints,
			&addressInfos);

		if (result != 0)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to get address information");
		}

		auto endpoints = std::vector<Endpoint>();

		for (auto i = addressInfos; i->ai_next != nullptr; i = i->ai_next)
		{
			auto endpoint = Endpoint();

			memcpy(
				&endpoint.storage,
				i->ai_addr,
				i->ai_addrlen);

			endpoints.push_back(endpoint);
		}

		freeaddrinfo(addressInfos);
		return std::move(endpoints);
	}
	void Endpoint::resolve(
		const Endpoint& endpoint,
		std::string& host,
		std::string& service)
	{
		if(!Engine::isNetworkInitialized())
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Network is not initialized");
		}

		auto socketAddress =
			reinterpret_cast<const sockaddr*>(&endpoint.storage);

		char hostString[NI_MAXHOST];
		char serviceString[NI_MAXSERV];

		auto flags =
			NI_NAMEREQD;

		auto result = getnameinfo(
			socketAddress,
			sizeof(sockaddr_storage),
			hostString,
			NI_MAXHOST,
			serviceString,
			NI_MAXSERV,
			flags);

		if (result != 0)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to get name information");
		}

		host = std::string(hostString);
		service = std::string(serviceString);
	}

	bool Endpoint::less(
		const Endpoint& a,
		const Endpoint& b)
	{
		auto& storage = a.storage;
		auto& otherStorage = b.storage;

		if (storage.ss_family != otherStorage.ss_family)
			return storage.ss_family < otherStorage.ss_family;

		if (storage.ss_family == AF_INET)
		{
			auto socketAddress4 =
				reinterpret_cast<const sockaddr_in*>(&storage);
			auto otherSocketAddress4 =
				reinterpret_cast<const sockaddr_in*>(&otherStorage);

			if (socketAddress4->sin_port != otherSocketAddress4->sin_port)
				return socketAddress4->sin_port < otherSocketAddress4->sin_port;

			return memcmp(
				&socketAddress4->sin_addr,
				&otherSocketAddress4->sin_addr,
				sizeof(in_addr)) < 0;
		}
		else if (storage.ss_family == AF_INET6)
		{
			auto socketAddress6 =
				reinterpret_cast<const sockaddr_in6*>(&storage);
			auto otherSocketAddress6 =
				reinterpret_cast<const sockaddr_in6*>(&otherStorage);

			if (socketAddress6->sin6_port != otherSocketAddress6->sin6_port)
				return socketAddress6->sin6_port < otherSocketAddress6->sin6_port;
			if (socketAddress6->sin6_scope_id != otherSocketAddress6->sin6_scope_id)
				return socketAddress6->sin6_scope_id < otherSocketAddress6->sin6_scope_id;
			if (socketAddress6->sin6_scope_id != otherSocketAddress6->sin6_scope_id)
				return socketAddress6->sin6_scope_id < otherSocketAddress6->sin6_scope_id;

			return memcmp(&socketAddress6->sin6_addr,
				&otherSocketAddress6->sin6_addr,
				sizeof(in6_addr)) < 0;
		}
		else
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Unsupported address family");
		}
	}
}
