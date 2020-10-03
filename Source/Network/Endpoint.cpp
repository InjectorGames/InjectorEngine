#include "Injector/Network/Endpoint.hpp"
#include "Injector/Defines.hpp"
#include "Injector/Exception/Exception.hpp"

#if INJECTOR_SYSTEM_LINUX || INJECTOR_SYSTEM_MACOS
#include <netdb.h>
#include <sys/socket.h>
#elif INJECTOR_SYSTEM_WINDOWS
#include <winsock2.h>
#else
#error Unknown operation system
#endif

namespace Injector
{
	Endpoint::Endpoint() noexcept
	{
		handle = new sockaddr_storage();

		memset(
			handle,
			0,
			sizeof(sockaddr_storage));
	}
	Endpoint::Endpoint(
		const Endpoint& endpoint) noexcept
	{
		handle = new sockaddr_storage();

		memcpy(
			handle,
			endpoint.handle,
			sizeof(sockaddr_storage));
	}
	Endpoint::~Endpoint()
	{
		auto socketAddress =
			static_cast<sockaddr_storage*>(handle);
		delete socketAddress;
	}

	void* Endpoint::getHandle() const noexcept
	{
		return handle;
	}

	bool Endpoint::getAddressFamily(AddressFamily& addressFamily) const noexcept
	{
		auto socketAddress =
			reinterpret_cast<sockaddr_storage*>(handle);

		if (socketAddress->ss_family == AF_INET)
			addressFamily = AddressFamily::IPv4;
		else if (socketAddress->ss_family == AF_INET6)
			addressFamily = AddressFamily::IPv6;
		else
			return false;

		return true;
	}
	bool Endpoint::getScopeID(uint32_t& scopeID) const noexcept
	{
		auto socketAddress =
			reinterpret_cast<sockaddr_storage*>(handle);

		if (socketAddress->ss_family != AF_INET6)
			return false;

		auto socketAddress6 =
			reinterpret_cast<sockaddr_in6*>(handle);

		scopeID = static_cast<uint32_t>(
			socketAddress6->sin6_scope_id);

		return true;
	}

	bool Endpoint::getAddress(std::string& address) const noexcept
	{
		auto socketAddress =
			reinterpret_cast<sockaddr*>(handle);

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
			return false;

		address = std::string(addressString);
		return true;
	}
	bool Endpoint::getAddress(std::vector<uint8_t>& address) const noexcept
	{
		auto socketAddress =
			reinterpret_cast<sockaddr_storage*>(handle);

		if (socketAddress->ss_family == AF_INET)
		{
			address = std::vector<uint8_t>(sizeof(in_addr));

			auto socketAddress4 =
				reinterpret_cast<sockaddr_in*>(handle);

			memcpy(
				address.data(),
				&socketAddress4->sin_addr,
				sizeof(in_addr));
		}
		else if (socketAddress->ss_family == AF_INET6)
		{
			address = std::vector<uint8_t>(sizeof(in6_addr));

			auto socketAddress6 =
				reinterpret_cast<sockaddr_in6*>(handle);

			memcpy(
				address.data(),
				&socketAddress6->sin6_addr,
				sizeof(in6_addr));
		}
		else
		{
			return false;
		}

		return true;
	}

	bool Endpoint::getPort(std::string& port) const noexcept
	{
		auto socketAddress =
			reinterpret_cast<sockaddr*>(handle);

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
			return false;

		port = std::string(portString);
		return true;
	}
	bool Endpoint::getPort(uint16_t& port) const noexcept
	{
		auto socketAddress =
			reinterpret_cast<sockaddr_storage*>(handle);

		if (socketAddress->ss_family == AF_INET)
		{
			auto socketAddress4 =
				reinterpret_cast<sockaddr_in*>(handle);
			port = static_cast<uint16_t>(
				socketAddress4->sin_port);
		}
		else if (socketAddress->ss_family == AF_INET6)
		{
			auto socketAddress6 =
				reinterpret_cast<sockaddr_in6*>(handle);
			port = static_cast<uint16_t>(
				socketAddress6->sin6_port);
		}
		else
		{
			return false;
		}

		return true;
	}

	bool Endpoint::getAddressAndPort(
		std::string& address,
		std::string& port) const noexcept
	{
		auto socketAddress =
			reinterpret_cast<sockaddr*>(handle);

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
			return false;

		address = std::string(addressString);
		port = std::string(portString);
		return true;
	}

	bool Endpoint::operator==(
		const Endpoint& endpoint) const noexcept
	{
		auto socketAddress =
			reinterpret_cast<sockaddr_storage*>(handle);
		auto otherSocketAddress =
			reinterpret_cast<sockaddr_storage*>(endpoint.handle);

		if (socketAddress->ss_family != otherSocketAddress->ss_family)
			return false;

		if (socketAddress->ss_family == AF_INET)
		{
			auto socketAddress4 =
				reinterpret_cast<sockaddr_in*>(handle);
			auto otherSocketAddress4 =
				reinterpret_cast<sockaddr_in*>(endpoint.handle);

			return
				socketAddress4->sin_port ==
					otherSocketAddress4->sin_port &&
				memcmp(&socketAddress4->sin_addr,
					&otherSocketAddress4->sin_addr,
					sizeof(in_addr)) == 0;
		}
		else if (socketAddress->ss_family == AF_INET6)
		{
			auto socketAddress6 =
				reinterpret_cast<sockaddr_in6*>(handle);
			auto otherSocketAddress6 =
				reinterpret_cast<sockaddr_in6*>(endpoint.handle);

			// TODO: add flow comparison?

			return
				socketAddress6->sin6_port ==
					otherSocketAddress6->sin6_port &&
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

	bool Endpoint::resolve(
		AddressFamily addressFamily,
		SocketType socketType,
		const std::string& host,
		const std::string& service,
		std::vector<Endpoint>& endpoints) noexcept
	{
		auto hints = addrinfo();

		memset(
			&hints,
			0,
			sizeof(addrinfo));

		hints.ai_flags =
			AI_ADDRCONFIG |
			AI_V4MAPPED;

		if(addressFamily == AddressFamily::IPv4)
			hints.ai_family = AF_INET;
		else if(addressFamily == AddressFamily::IPv6)
			hints.ai_family = AF_INET6;

		if(socketType == SocketType::Stream)
			hints.ai_socktype = SOCK_STREAM;
		else if(socketType == SocketType::Datagram)
			hints.ai_socktype = SOCK_DGRAM;

		addrinfo* addressInfos;

		auto result = getaddrinfo(
			host.c_str(),
			service.c_str(),
			&hints,
			&addressInfos);

		if (result != 0)
			return false;

		endpoints = std::vector<Endpoint>();

		for (auto i = addressInfos; i->ai_next != nullptr; i = i->ai_next)
		{
			auto endpoint = Endpoint();

			memcpy(
				endpoint.handle,
				i->ai_addr,
				i->ai_addrlen);

			endpoints.push_back(std::move(endpoint));
		}

		freeaddrinfo(addressInfos);
		return true;
	}
	bool Endpoint::resolve(
		const Endpoint& endpoint,
		std::string& host,
		std::string& service) noexcept
	{
		auto socketAddress =
			reinterpret_cast<sockaddr*>(endpoint.handle);

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
			return false;

		host = std::string(hostString);
		service = std::string(serviceString);
		return true;
	}

	bool Endpoint::create(
		const std::string& address,
		const std::string& port,
		Endpoint& endpoint) noexcept
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
			return false;

		endpoint = Endpoint();

		memcpy(
			endpoint.handle,
			addressInfos->ai_addr,
			addressInfos->ai_addrlen);

		freeaddrinfo(addressInfos);
		return true;
	}

	bool Endpoint::less(
		const Endpoint& a,
		const Endpoint& b) noexcept
	{
		auto socketAddress =
			reinterpret_cast<sockaddr_storage*>(a.handle);
		auto otherSocketAddress =
			reinterpret_cast<sockaddr_storage*>(b.handle);

		if (socketAddress->ss_family != otherSocketAddress->ss_family)
			return socketAddress->ss_family < otherSocketAddress->ss_family;

		if (socketAddress->ss_family == AF_INET)
		{
			auto socketAddress4 =
				reinterpret_cast<sockaddr_in*>(a.handle);
			auto otherSocketAddress4 =
				reinterpret_cast<sockaddr_in*>(b.handle);

			if (socketAddress4->sin_port != otherSocketAddress4->sin_port)
				return socketAddress4->sin_port < otherSocketAddress4->sin_port;

			return memcmp(
				&socketAddress4->sin_addr,
				&otherSocketAddress4->sin_addr,
				sizeof(in_addr)) < 0;
		}
		else if (socketAddress->ss_family == AF_INET6)
		{
			auto socketAddress6 =
				reinterpret_cast<sockaddr_in6*>(a.handle);
			auto otherSocketAddress6 =
				reinterpret_cast<sockaddr_in6*>(b.handle);

			// TODO: add flow comparison?

			if (socketAddress6->sin6_port != otherSocketAddress6->sin6_port)
				return socketAddress6->sin6_port < otherSocketAddress6->sin6_port;
			if (socketAddress6->sin6_scope_id != otherSocketAddress6->sin6_scope_id)
				return socketAddress6->sin6_scope_id < otherSocketAddress6->sin6_scope_id;

			return memcmp(&socketAddress6->sin6_addr,
				&otherSocketAddress6->sin6_addr,
				sizeof(in6_addr)) < 0;
		}
		else
		{
			return false;
		}
	}
}
