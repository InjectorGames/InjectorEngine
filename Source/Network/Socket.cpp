#include "Injector/Network/Socket.hpp"
#include "Injector/Engine.hpp"
#include "Injector/Exception/Exception.hpp"

#if INJECTOR_SYSTEM_LINUX || INJECTOR_SYSTEM_MACOS
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#define NULL_SOCKET -1
#elif INJECTOR_SYSTEM_WINDOWS
#include <winsock2.h>
#define NULL_SOCKET INVALID_SOCKET
#else
#error Unknown operating system
#endif

namespace Injector
{
	Socket::Socket() noexcept :
		family(SocketFamily::Unspecified),
		protocol(SocketProtocol::Unspecified),
		handle(NULL_SOCKET)
	{
	}
	Socket::Socket(
		SocketFamily _family,
		SocketProtocol _protocol) :
		family(_family),
		protocol(_protocol)
	{
		if(!Engine::isNetworkInitialized())
		{
			throw Exception(
				"Socket",
				"Socket",
				"Network is not initialized");
		}

		int socketFamily;

		if (_family == SocketFamily::IPv4)
		{
			socketFamily = AF_INET;
		}
		else if (_family == SocketFamily::IPv6)
		{
			socketFamily = AF_INET6;
		}
		else
		{
			throw Exception(
				"Socket",
				"Socket",
				"Unsupported address family");
		}

		int socketType;
		int socketProtocol;

		if(_protocol == SocketProtocol::TCP)
		{
			socketType = SOCK_STREAM;
			socketProtocol = IPPROTO_TCP;
		}
		else if(_protocol == SocketProtocol::UDP)
		{
			socketType = SOCK_DGRAM;
			socketProtocol = IPPROTO_UDP;
		}
		else
		{
			throw Exception(
				"Socket",
				"Socket",
				"Unsupported protocol type");
		}

		auto socket = ::socket(
			socketFamily,
			socketType,
			socketProtocol);

		if(socket == NULL_SOCKET)
		{
			throw Exception(
				"Socket",
				"Socket",
				"Failed to create socket");
		}

		handle = socket;
	}
	Socket::Socket(Socket&& socket) noexcept
	{
		family = socket.family;
		protocol = socket.protocol;
		handle = socket.handle;
		socket.handle = NULL_SOCKET;
	}
	Socket::~Socket()
	{
		shutdown(SocketShutdown::Both);
		close();
	}

	SocketFamily Socket::getAddressFamily() const noexcept
	{
		return family;
	}
	SocketProtocol Socket::getProtocolType() const noexcept
	{
		return protocol;
	}

	bool Socket::getIsListening() const
	{
		bool listening;
		socklen_t length = sizeof(bool);

		auto result = ::getsockopt(
			handle,
			SOL_SOCKET,
			SO_ACCEPTCONN,
			&listening,
			&length);

		if(result != 0)
		{
			throw Exception(
				"Socket",
				"getIsListening",
				"Failed to get socket option");
		}

		return listening;
	}

	Endpoint Socket::getLocalEndpoint() const
	{
		auto endpoint = Endpoint();

		auto address = reinterpret_cast<sockaddr*>(
			endpoint.getHandle());
		socklen_t length =
			sizeof(sockaddr_storage);

		auto result = ::getsockname(
			handle,
			address,
			&length);

		if (result != 0)
		{
			throw Exception(
				"Socket",
				"getLocalEndpoint",
				"Failed to get socket name");
		}

		return endpoint;
	}
	Endpoint Socket::getRemoteEndpoint() const
	{
		auto endpoint = Endpoint();

		auto address = reinterpret_cast<sockaddr*>(
			endpoint.getHandle());
		socklen_t length =
			sizeof(sockaddr_storage);

		auto result = ::getpeername(
			handle,
			address,
			&length);

		if (result != 0)
		{
			throw Exception(
				"Socket",
				"getRemoteEndpoint",
				"Failed to get socket name");
		}

		return endpoint;
	}

	void Socket::setBlocking(bool blocking) const
	{
#if INJECTOR_SYSTEM_LINUX || INJECTOR_SYSTEM_MACOS
		auto flags = fcntl(
			handle,
			F_GETFL,
			0);

		if (flags == -1)
		{
			throw Exception(
				"Socket",
				"setBlocking",
				"Failed to get flags");
		}

		flags = blocking ?
			(flags & ~O_NONBLOCK) :
			(flags | O_NONBLOCK);

		auto result = fcntl(
			handle,
			F_SETFL,
			flags);

		if (result == -1)
		{
			throw Exception(
				"Socket",
				"setBlocking",
				"Failed to set flags");
		}
#elif INJECTOR_SYSTEM_WINDOWS
		u_long mode = blocking ?
			0 :
			1;

		auto result = ioctlsocket(
			handle,
			FIONBIO,
			&mode);

   		if(result != 0)
   		{
			throw Exception(
				"Socket",
				"setBlockingMode",
				"Failed to set socket mode");
   		}
#endif
	}

	void Socket::bind(const Endpoint& endpoint)
	{
		auto address = reinterpret_cast<const sockaddr*>(
			endpoint.getHandle());
		auto family = endpoint.getSocketFamily();

		socklen_t length;

		if(family == SocketFamily::IPv4)
		{
			length = sizeof(sockaddr_in);
		}
		else if(family == SocketFamily::IPv6)
		{
			length = sizeof(sockaddr_in6);
		}
		else
		{
			throw Exception(
				"Socket",
				"bind",
				"Unsupported address family");
		}

		auto result = ::bind(
			handle,
			address,
			length);

		if(result != 0)
		{
			throw Exception(
				"Socket",
				"bind",
				"Failed to bind socket");
		}
	}
	void Socket::listen()
	{
		auto result = ::listen(
			handle,
			SOMAXCONN);

		if(result != 0)
		{
			throw Exception(
				"Socket",
				"listen",
				"Failed to listen socket");
		}
	}

	bool Socket::accept(
		Socket& socket,
		Endpoint& endpoint) noexcept
	{
		auto address = reinterpret_cast<sockaddr*>(
			endpoint.getHandle());
		socklen_t length =
			sizeof(sockaddr_storage);

		auto result = ::accept(
			handle,
			address,
			&length);

		if (result == NULL_SOCKET)
			return false;

		socket = Socket();
		socket.family = family;
		socket.protocol = protocol;
		socket.handle = result;
		return true;
	}
	bool Socket::connect(const Endpoint& endpoint) noexcept
	{
		auto address = reinterpret_cast<const sockaddr*>(
			endpoint.getHandle());
		auto family = endpoint.getSocketFamily();

		socklen_t length;

		if(family == SocketFamily::IPv4)
			length = sizeof(sockaddr_in);
		else if(family == SocketFamily::IPv6)
			length = sizeof(sockaddr_in6);
		else
			return false;

		auto result = ::connect(
			handle,
			address,
			length);

		return result == 0;
	}

	int Socket::receive(
		void* buffer,
		size_t size) noexcept
	{
		return ::recv(
			handle,
			buffer,
			size,
			0);
	}
	int Socket::send(
		const void* buffer,
		size_t size) noexcept
	{
		return ::send(
			handle,
			buffer,
			size,
			0);
	}

	int Socket::receiveFrom(
		void* buffer,
		size_t size,
		Endpoint& endpoint) noexcept
	{
		auto address = reinterpret_cast<sockaddr*>(
			endpoint.getHandle());
		socklen_t length =
			sizeof(sockaddr_storage);

		auto result = ::recvfrom(
			handle,
			buffer,
			size,
			0,
			address,
			&length);

		if(result < 0)
			return result;

		return result;
	}
	int Socket::sendTo(
		const void* buffer,
		size_t size,
		const Endpoint& endpoint) noexcept
	{
		auto address = reinterpret_cast<const sockaddr*>(
			endpoint.getHandle());

		return ::sendto(
			handle,
			buffer,
			size,
			0,
			address,
			sizeof(sockaddr_storage));
	}

	bool Socket::shutdown(
		SocketShutdown shutdown) noexcept
	{
		int shutdownType;

		if(shutdown == SocketShutdown::Receive)
			shutdownType = SHUT_RD;
		else if(shutdown == SocketShutdown::Send)
			shutdownType =  SHUT_WR;
		else if(shutdown == SocketShutdown::Both)
			shutdownType = SHUT_RDWR;
		else
			return false;

		auto result = ::shutdown(
			handle,
			shutdownType);

		return result == 0;
	}
	bool Socket::close() noexcept
	{
		handle = NULL_SOCKET;
		return ::close(handle) == 0;
	}

	bool Socket::operator==(
		const Socket& socket) const noexcept
	{
		return handle == socket.handle;
	}
	bool Socket::operator!=(
		const Socket& socket) const noexcept
	{
		return handle != socket.handle;
	}

	Socket& Socket::operator=(
		Socket&& socket) noexcept
	{
		if(this != &socket)
		{
			family = socket.family;
			protocol = socket.protocol;
			handle = socket.handle;
			socket.family = SocketFamily::Unspecified;
			socket.protocol = SocketProtocol::Unspecified;
			socket.handle = NULL_SOCKET;
		}

		return *this;
	}

	bool Socket::less(
		const Socket& a,
		const Socket& b) noexcept
	{
		return a.handle < b.handle;
	}
}