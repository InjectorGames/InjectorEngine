#include "Injector/Network/Endpoint.hpp"
#include "Injector/Defines.hpp"
#include "Injector/Exception/NullException.hpp"

#if INJECTOR_SYSTEM_LINUX || INJECTOR_SYSTEM_MACOS
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#elif INJECTOR_SYSTEM_WINDOWS
#include <winsock2.h>
#else
#error Unknown operation system
#endif

namespace Injector
{
	Endpoint::Endpoint() :
		handle(nullptr)
	{
	}
	Endpoint::Endpoint(
		Endpoint& endpoint)
	{
		if(endpoint.handle)
		{
			handle = new sockaddr_storage();

			auto socketAddress =
				static_cast<sockaddr_storage*>(endpoint.handle);

			memcpy(
				handle,
				socketAddress,
				sizeof(sockaddr_storage));
		}
		else
		{
			handle = nullptr;
		}
	}
	Endpoint::Endpoint(
		Endpoint&& endpoint) noexcept :
		handle(endpoint.handle)
	{
		endpoint.handle = nullptr;
	}
	Endpoint::~Endpoint()
	{
		if(handle)
		{
			auto socketAddress =
				static_cast<sockaddr_storage*>(handle);
			delete socketAddress;
		}
	}

	bool Endpoint::isValid() const noexcept
	{
		return !handle;
	}

	bool Endpoint::getFamily(SocketFamily& family) const noexcept
	{
		if(!handle)
			return false;

		auto socketAddress =
			reinterpret_cast<sockaddr_storage*>(handle);

		if(socketAddress->ss_family == AF_INET)
			family = SocketFamily::IPv4;
		else if(socketAddress->ss_family == AF_INET6)
			family = SocketFamily::IPv6;
		else
			return false;

		return true;
	}

	bool Endpoint::getAddress(std::string& address) const noexcept
	{
		if(!handle)
			return false;

		auto socketAddress =
			reinterpret_cast<sockaddr*>(handle);

		char addressString[NI_MAXHOST];

		auto flags =
			NI_NUMERICHOST;

		auto result = getnameinfo(
			socketAddress,
			socketAddress->sa_len,
			addressString,
			NI_MAXHOST,
			nullptr,
			0,
			flags);

		if(result != 0)
			return false;

		address = std::string(addressString);
		return true;
	}

	bool Endpoint::getPort(std::string& port) const noexcept
	{
		if(!handle)
			return false;

		auto socketAddress =
			reinterpret_cast<sockaddr*>(handle);

		char portString[NI_MAXSERV];

		auto flags =
			NI_NUMERICSERV;

		auto result = getnameinfo(
			socketAddress,
			socketAddress->sa_len,
			nullptr,
			0,
			portString,
			NI_MAXSERV,
			flags);

		if(result != 0)
			return false;

		port = std::string(portString);
		return true;
	}
	bool Endpoint::getPort(uint16_t& port) const noexcept
	{
		if(!handle)
			return false;

		auto socketAddress =
			reinterpret_cast<sockaddr_storage*>(handle);

		if(socketAddress->ss_family == AF_INET)
		{
			auto socketAddress4 =
				reinterpret_cast<sockaddr_in*>(handle);
			port = static_cast<uint16_t>(
				socketAddress4->sin_port);
			return true;
		}
		else if(socketAddress->ss_family == AF_INET6)
		{
			auto socketAddress6 =
				reinterpret_cast<sockaddr_in6*>(handle);
			port = static_cast<uint16_t>(
				socketAddress6->sin6_port);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Endpoint::getAddressAndPort(
		std::string& address,
		std::string& port) const noexcept
	{
		if(!handle)
			return false;

		auto socketAddress =
			reinterpret_cast<sockaddr*>(handle);

		char addressString[NI_MAXHOST];
		char portString[NI_MAXSERV];

		auto flags =
			NI_NUMERICHOST |
			NI_NUMERICSERV;

		auto result = getnameinfo(
			socketAddress,
			socketAddress->sa_len,
			addressString,
			NI_MAXHOST,
			portString,
			NI_MAXSERV,
			flags);

		if(result != 0)
			return false;

		address = std::string(addressString);
		port = std::string(portString);
		return true;
	}

	bool Endpoint::operator==(
		const Endpoint& endpoint) const noexcept
	{
		if (handle)
		{
			if (!endpoint.handle)
				return false;

			auto socketAddress =
				reinterpret_cast<sockaddr_storage*>(handle);
			auto otherSocketAddress =
				reinterpret_cast<sockaddr_storage*>(endpoint.handle);

			if(socketAddress->ss_family != otherSocketAddress->ss_family)
				return false;

			if(socketAddress->ss_family == AF_INET)
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
			else if(socketAddress->ss_family == AF_INET6)
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
		else
		{
			return !endpoint.handle;
		}
	}
	bool Endpoint::operator!=(
		const Endpoint& endpoint) const noexcept
	{
		return !(*this == endpoint);
	}

	Endpoint Endpoint::create(
		const std::string& address,
		const std::string& port)
	{
		auto hints = addrinfo();
		memset(&hints, 0, sizeof(addrinfo));

		hints.ai_flags =
			AI_NUMERICHOST |
			AI_NUMERICSERV;

		addrinfo* addressInfos;

		auto result = getaddrinfo(
			address.c_str(),
			port.c_str(),
			&hints,
			&addressInfos);

		if(result != 0)
		{
			throw Exception(
				"Endpoint",
				"create",
				"Failed to get address info");
		}

		auto endpoint = Endpoint();

		auto socketAddress = reinterpret_cast<sockaddr_storage*>(
			addressInfos->ai_addr);

		endpoint.handle = new sockaddr_storage();

		memcpy(
			endpoint.handle,
			socketAddress,
			sizeof(sockaddr_storage));

		freeaddrinfo(addressInfos);
		return std::move(endpoint);
	}
	bool Endpoint::create(
		const std::string& address,
		const std::string& port,
		Endpoint& endpoint) noexcept
	{
		auto hints = addrinfo();
		memset(&hints, 0, sizeof(addrinfo));

		hints.ai_flags =
			AI_NUMERICHOST |
			AI_NUMERICSERV;

		addrinfo* addressInfos;

		auto result = getaddrinfo(
			address.c_str(),
			port.c_str(),
			&hints,
			&addressInfos);

		if(result != 0)
			return false;

		auto socketAddress = reinterpret_cast<sockaddr_storage*>(
			addressInfos->ai_addr);

		endpoint.handle = new sockaddr_storage();

		memcpy(
			endpoint.handle,
			socketAddress,
			sizeof(sockaddr_storage));

		freeaddrinfo(addressInfos);
		return true;
	}

	std::vector<Endpoint> Endpoint::resolve(
		const std::string& host,
		const std::string& service)
	{
		addrinfo* addressInfos;

		auto result = getaddrinfo(
			host.c_str(),
			service.c_str(),
			nullptr,
			&addressInfos);

		if(result != 0)
		{
			throw Exception(
				"Endpoint",
				"resolve",
				"Failed to get address info");
		}

		auto endpoints = std::vector<Endpoint>();

		for (auto i = addressInfos; i->ai_next != nullptr; i = i->ai_next)
		{
			auto endpoint = Endpoint();

			auto socketAddress =
				reinterpret_cast<sockaddr_storage*>(i->ai_addr);

			endpoint.handle = new sockaddr_storage();

			memcpy(
				endpoint.handle,
				socketAddress,
				sizeof(sockaddr_storage));

			endpoints.push_back(std::move(endpoint));
		}

		freeaddrinfo(addressInfos);
		return std::move(endpoints);
	}
	bool Endpoint::resolve(
		const std::string& host,
		const std::string& service,
		std::vector<Endpoint>& endpoints) noexcept
	{
		addrinfo* addressInfos;

		auto result = getaddrinfo(
			host.c_str(),
			service.c_str(),
			nullptr,
			&addressInfos);

		if(result != 0)
			return false;

		for (auto i = addressInfos; i->ai_next != nullptr; i = i->ai_next)
		{
			auto endpoint = Endpoint();

			auto socketAddress =
				reinterpret_cast<sockaddr_storage*>(i->ai_addr);

			endpoint.handle = new sockaddr_storage();

			memcpy(
				endpoint.handle,
				socketAddress,
				sizeof(sockaddr_storage));

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
		if(!endpoint.handle)
			return false;

		auto socketAddress =
			reinterpret_cast<sockaddr*>(endpoint.handle);

		char hostString[NI_MAXHOST];
		char serviceString[NI_MAXSERV];

		auto flags =
			NI_NAMEREQD;

		auto result = getnameinfo(
			socketAddress,
			socketAddress->sa_len,
			hostString,
			NI_MAXHOST,
			serviceString,
			NI_MAXSERV,
			flags);

		if(result != 0)
			return false;

		host = std::string(hostString);
		service = std::string(serviceString);
		return true;
	}

	static bool less(
		const Endpoint& a,
		const Endpoint& b) noexcept
	{
		if(a.handle)
		{
			if(!b.handle)
				return false;

			auto socketAddress =
				reinterpret_cast<sockaddr_storage*>(a.handle);
			auto otherSocketAddress =
				reinterpret_cast<sockaddr_storage*>(b.handle);

			if(socketAddress->ss_family != otherSocketAddress->ss_family)
				return socketAddress->ss_family < otherSocketAddress->ss_family;

			if(socketAddress->ss_family == AF_INET)
			{
				auto socketAddress4 =
					reinterpret_cast<sockaddr_in*>(a.handle);
				auto otherSocketAddress4 =
					reinterpret_cast<sockaddr_in*>(b.handle);

				if(socketAddress4->sin_port != otherSocketAddress4->sin_port)
					return socketAddress4->sin_port < otherSocketAddress4->sin_port;

				return memcmp(
					&socketAddress4->sin_addr,
					&otherSocketAddress4->sin_addr,
					sizeof(in_addr)) < 0;
			}
			else if(socketAddress->ss_family == AF_INET6)
			{
				auto socketAddress6 =
					reinterpret_cast<sockaddr_in6*>(a.handle);
				auto otherSocketAddress6 =
					reinterpret_cast<sockaddr_in6*>(b.handle);

				// TODO: add flow comparison?

				if(socketAddress6->sin6_port != otherSocketAddress6->sin6_port)
					return socketAddress6->sin6_port < otherSocketAddress6->sin6_port;
				if(socketAddress6->sin6_scope_id != otherSocketAddress6->sin6_scope_id)
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
		else
		{
			return false;
		}
	}
}
