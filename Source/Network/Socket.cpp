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
	static int toSocketFamily(SocketFamily family)
	{
		if(family == SocketFamily::IPv4)
		{
			return AF_INET;
		}
		else if(family == SocketFamily::IPv6)
		{
			return AF_INET6;
		}
		else
		{
			throw Exception(
				"",
				"toSocketFamily",
				"Unsupported socket family");
		}
	}
	static int toSocketType(SocketType type)
	{
		if(type == SocketType::Stream)
		{
			return SOCK_STREAM;
		}
		else if(type == SocketType::Datagram)
		{
			return SOCK_DGRAM;
		}
		else
		{
			throw Exception(
				"",
				"toSocketType",
				"Unsupported socket type");
		}
	}
	static int toSocketShutdown(SocketShutdown shutdown)
	{
		if(shutdown == SocketShutdown::ReadOnly)
		{
			return SHUT_RD;
		}
		else if(shutdown == SocketShutdown::WriteOnly)
		{
			return SHUT_WR;
		}
		else if(shutdown == SocketShutdown::ReadWrite)
		{
			return SHUT_RDWR;
		}
		else
		{
			throw Exception(
				"",
				"toSocketShutdown",
				"Unsupported socket shutdown");
		}
	}

	Socket::Socket(
		SocketFamily _family,
		SocketType _type) :
		family(_family),
		type(_type)
	{
		handle = static_cast<uint64_t>(socket(
			toSocketFamily(family),
			toSocketType(type),
			0));

		if(handle == NULL_SOCKET)
		{
			throw Exception(
				"Socket",
				"Socket",
				"Failed to create");
		}
	}
	Socket::~Socket()
	{
		shutdown(SocketShutdown::ReadWrite);
		close();
	}

	bool Socket::shutdown(
		SocketShutdown shutdown) noexcept
	{
		return ::shutdown(
			static_cast<int>(handle),
			toSocketShutdown(shutdown)) == 0;
	}
	bool Socket::close() noexcept
	{
		handle = NULL_SOCKET;

		return ::close(
			static_cast<int>(handle)) == 0;
	}
}
