#include "Injector/Network/Socket.hpp"
#include "Injector/Defines.hpp"
#include "Injector/Exception/Exception.hpp"

#if INJECTOR_SYSTEM_LINUX || INJECTOR_SYSTEM_MACOS
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#define NULL_SOCKET -1
#elif INJECTOR_SYSTEM_WINDOWS
#include <winsock2.h>
#define NULL_SOCKET INVALID_SOCKET
#else
#error Unknown operation system
#endif

namespace Injector
{
	Socket::Socket() noexcept :
		handle(NULL_SOCKET)
	{
	}
	Socket::~Socket()
	{
		shutdown(SocketShutdown::Both);
		close();
	}

	bool Socket::isValid() noexcept
	{
		return handle != NULL_SOCKET;
	}

	bool Socket::getIsListening(bool& listening) noexcept
	{
		bool value;
		socklen_t length = sizeof(bool);

		auto result = ::getsockopt(
			static_cast<int>(handle),
			SOL_SOCKET,
			SO_ACCEPTCONN,
			&value,
			&length);

		if(result != 0)
			return false;

		listening = value;
		return true;
	}
	bool Socket::getSocketType(SocketType& socketType) noexcept
	{
		int value;
		socklen_t length = sizeof(int);

		auto result = ::getsockopt(
			static_cast<int>(handle),
			SOL_SOCKET,
			SO_TYPE,
			&value,
			&length);

		if(result != 0)
			return false;

		if(value == SOCK_STREAM)
			socketType = SocketType::Stream;
		else if(value == SOCK_DGRAM)
			socketType = SocketType::Datagram;
		else
			return false;

		return true;
	}

	bool Socket::getLocalEndpoint(
		Endpoint& endpoint) noexcept
	{
		auto newEndpoint = Endpoint();

		auto socketAddress = reinterpret_cast<sockaddr*>(
			newEndpoint.getHandle());
		socklen_t addressLength =
			sizeof(sockaddr_storage);

		auto result = ::getsockname(
			static_cast<int>(handle),
			socketAddress,
			&addressLength);

		if (result != 0)
			return false;

		endpoint = newEndpoint;
		return true;
	}
	bool Socket::getRemoteEndpoint(
		Endpoint& endpoint) noexcept
	{
		auto newEndpoint = Endpoint();

		auto socketAddress = reinterpret_cast<sockaddr*>(
			newEndpoint.getHandle());
		socklen_t addressLength =
			sizeof(sockaddr_storage);

		auto result = ::getpeername(
			static_cast<int>(handle),
			socketAddress,
			&addressLength);

		if (result != 0)
			return false;

		endpoint = newEndpoint;
		return true;
	}

	bool Socket::bind(const Endpoint& endpoint) noexcept
	{
		auto socketAddress =
			reinterpret_cast<const sockaddr*>(endpoint.getHandle());

		return ::bind(
			static_cast<int>(handle),
			socketAddress,
			sizeof(sockaddr_storage)) == 0;
	}
	bool Socket::connect(const Endpoint& endpoint) noexcept
	{
		auto socketAddress =
			reinterpret_cast<const sockaddr*>(endpoint.getHandle());

		return ::connect(
			static_cast<int>(handle),
			socketAddress,
			sizeof(sockaddr_storage)) == 0;
	}

	bool Socket::listen() noexcept
	{
		return ::listen(
			static_cast<int>(handle),
			SOMAXCONN) == 0;
	}
	bool Socket::accept(
		Endpoint& endpoint,
		Socket& socket) noexcept
	{
		auto newEndpoint = Endpoint();

		auto socketAddress =
			reinterpret_cast<sockaddr*>(endpoint.getHandle());
		socklen_t addressLength =
			sizeof(sockaddr_storage);

		auto result = ::accept(
			static_cast<int>(handle),
			socketAddress,
			&addressLength);

		if (result != 0)
			return false;

		endpoint = newEndpoint;

		socket = Socket();
		socket.handle = handle;
		return true;
	}

	int Socket::receive(
		void* buffer,
		size_t size) noexcept
	{
		return static_cast<int>(::recv(
			static_cast<int>(handle),
			buffer,
			size,
			0));
	}
	int Socket::send(
		const void* buffer,
		size_t size) noexcept
	{
		return static_cast<int>(::send(
			static_cast<int>(handle),
			buffer,
			size,
			0));
	}

	int Socket::receiveFrom(
		void* buffer,
		size_t size,
		Endpoint& endpoint) noexcept
	{
		auto newEndpoint = Endpoint();

		auto socketAddress = reinterpret_cast<sockaddr*>(
			newEndpoint.getHandle());
		socklen_t addressLength =
			sizeof(sockaddr_storage);

		auto result = ::recvfrom(
			static_cast<int>(handle),
			buffer,
			size,
			0,
			socketAddress,
			&addressLength);

		if(result == -1)
			return false;

		endpoint = std::move(newEndpoint);
		return result;
	}
	int Socket::sendTo(
		void* buffer,
		size_t size,
		const Endpoint& endpoint) noexcept
	{
		auto socketAddress = reinterpret_cast<const sockaddr*>(
			endpoint.getHandle());

		return static_cast<int>(::sendto(
			static_cast<int>(handle),
			buffer,
			size,
			0,
			socketAddress,
			sizeof(sockaddr_storage)));
	}

	bool Socket::shutdown(
		SocketShutdown shutdown) noexcept
	{
		int shutdownType;

		if(shutdown == SocketShutdown::Read)
		{
			shutdownType = SHUT_RD;
		}
		else if(shutdown == SocketShutdown::Write)
		{
			shutdownType =  SHUT_WR;
		}
		else if(shutdown == SocketShutdown::Both)
		{
			shutdownType = SHUT_RDWR;
		}
		else
		{
			throw Exception(
				"Socket",
				"shutdown",
				"Unsupported shutdown type");
		}

		return ::shutdown(
			static_cast<int>(handle),
			shutdownType) == 0;
	}
	bool Socket::close() noexcept
	{
		handle = NULL_SOCKET;

		return ::close(
			static_cast<int>(handle));;
	}

	bool Socket::create(
		AddressFamily family,
		SocketType type,
		Socket& socket) noexcept
	{
		int addressFamily;

		if (family == AddressFamily::IPv4)
			addressFamily = AF_INET;
		else if (family == AddressFamily::IPv6)
			addressFamily = AF_INET6;
		else
			return false;

		int socketType;

		if(type == SocketType::Stream)
			socketType =  SOCK_STREAM;
		else if(type == SocketType::Datagram)
			socketType = SOCK_DGRAM;
		else
			return false;

		auto handle = static_cast<uint64_t>(::socket(
			addressFamily,
			socketType,
			0));

		if(handle == NULL_SOCKET)
			return false;

		socket = Socket();
		socket.handle = handle;
		return true;
	}
}
