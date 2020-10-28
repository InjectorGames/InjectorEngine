#include "Injector/Network/Socket.hpp"
#include "Injector/Engine.hpp"
#include "Injector/Exception/Exception.hpp"

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
				THIS_FUNCTION_NAME,
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
				THIS_FUNCTION_NAME,
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
				THIS_FUNCTION_NAME,
				"Unsupported protocol type");
		}

		auto socket = ::socket(
			socketFamily,
			socketType,
			socketProtocol);

		if(socket == NULL_SOCKET)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
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
	SOCKET_TYPE Socket::getHandle() const noexcept
	{
		return handle;
	}

	bool Socket::isListening() const
	{
		bool listening;
		socklen_t length = sizeof(bool);

		auto result = ::getsockopt(
			handle,
			SOL_SOCKET,
			SO_ACCEPTCONN,
			reinterpret_cast<char*>(&listening),
			&length);

		if(result != 0)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to get socket option");
		}

		return listening;
	}

	Endpoint Socket::getLocalEndpoint() const
	{
		auto endpoint = Endpoint();

		auto address = reinterpret_cast<sockaddr*>(
			&endpoint.getStorage());
		socklen_t length =
			sizeof(sockaddr_storage);

		auto result = ::getsockname(
			handle,
			address,
			&length);

		if (result != 0)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to get socket name");
		}

		return endpoint;
	}
	Endpoint Socket::getRemoteEndpoint() const
	{
		auto endpoint = Endpoint();

		auto address = reinterpret_cast<sockaddr*>(
			&endpoint.getStorage());
		socklen_t length =
			sizeof(sockaddr_storage);

		auto result = ::getpeername(
			handle,
			address,
			&length);

		if (result != 0)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
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
				THIS_FUNCTION_NAME,
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
				THIS_FUNCTION_NAME,
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
				std::string(typeid(Socket).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Failed to set socket mode");
   		}
#endif
	}

	uint32_t Socket::getReceiveTimeout() const
	{
#if INJECTOR_SYSTEM_LINUX || INJECTOR_SYSTEM_MACOS
		timeval timeout;
		socklen_t size = sizeof(timeval);

		auto result = getsockopt(
			handle,
			SOL_SOCKET,
			SO_RCVTIMEO,
			&timeout,
			&size);

		if(result != 0)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to get socket option");
		}

		return
			timeout.tv_sec * 1000 +
			timeout.tv_usec / 1000;
#elif INJECTOR_SYSTEM_WINDOWS
		uint32_t timeout;
		int size = sizeof(uint32_t);

		auto result = getsockopt(
			handle,
			SOL_SOCKET,
			SO_RCVTIMEO,
			reinterpret_cast<char*>(&timeout),
			&size);

		if(result != 0)
		{
			throw Exception(
				std::string(typeid(Socket).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Failed to get socket option");
		}

		return static_cast<size_t>(timeout);
#endif
	}
	void Socket::setReceiveTimeout(uint32_t milliseconds) const
	{
#if INJECTOR_SYSTEM_LINUX || INJECTOR_SYSTEM_MACOS
		timeval timeout;
		timeout.tv_sec = milliseconds / 1000;
		timeout.tv_usec = (milliseconds % 1000) * 1000;

		auto result = setsockopt(
			handle,
			SOL_SOCKET,
			SO_RCVTIMEO,
			&timeout,
			sizeof(timeval));

		if(result != 0)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to set socket option");
		}
#elif INJECTOR_SYSTEM_WINDOWS
		auto result = setsockopt(
			handle,
			SOL_SOCKET,
			SO_RCVTIMEO,
			reinterpret_cast<const char*>(&milliseconds),
			sizeof(uint32_t));

		if(result != 0)
		{
			throw Exception(
				std::string(typeid(Socket).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Failed to set socket option");
		}
#endif
	}

	uint32_t Socket::getSendTimeout() const
	{
#if INJECTOR_SYSTEM_LINUX || INJECTOR_SYSTEM_MACOS
		timeval timeout;
		socklen_t size = sizeof(timeval);

		auto result = getsockopt(
			handle,
			SOL_SOCKET,
			SO_SNDTIMEO,
			&timeout,
			&size);

		if(result != 0)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to get socket option");
		}

		return
			timeout.tv_sec * 1000 +
			timeout.tv_usec / 1000;
#elif INJECTOR_SYSTEM_WINDOWS
		uint32_t timeout;
		int size = sizeof(uint32_t);

		auto result = getsockopt(
			handle,
			SOL_SOCKET,
			SO_SNDTIMEO,
			reinterpret_cast<char*>(&timeout),
			&size);

		if(result != 0)
		{
			throw Exception(
				std::string(typeid(Socket).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Failed to get socket option");
		}

		return static_cast<size_t>(timeout);
#endif
	}
	void Socket::setSendTimeout(uint32_t milliseconds) const
	{
#if INJECTOR_SYSTEM_LINUX || INJECTOR_SYSTEM_MACOS
		timeval timeout;
		timeout.tv_sec = milliseconds / 1000;
		timeout.tv_usec = (milliseconds % 1000) * 1000;

		auto result = setsockopt(
			handle,
			SOL_SOCKET,
			SO_RCVTIMEO,
			&timeout,
			sizeof(timeval));

		if(result != 0)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to set socket option");
		}
#elif INJECTOR_SYSTEM_WINDOWS
		auto result = setsockopt(
			handle,
			SOL_SOCKET,
			SO_RCVTIMEO,
			reinterpret_cast<const char*>(&milliseconds),
			sizeof(uint32_t));

		if(result != 0)
		{
			throw Exception(
				std::string(typeid(Socket).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Failed to set socket option");
		}
#endif
	}

	void Socket::bind(const Endpoint& endpoint)
	{
		auto address = reinterpret_cast<const sockaddr*>(
			&endpoint.getStorage());
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
				THIS_FUNCTION_NAME,
				"Unsupported address family");
		}

		auto result = ::bind(
			handle,
			address,
			length);

		if(result != 0)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
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
				THIS_FUNCTION_NAME,
				"Failed to listen socket");
		}
	}

	bool Socket::accept(
		Socket& socket,
		Endpoint& endpoint) noexcept
	{
		auto address = reinterpret_cast<sockaddr*>(
			&endpoint.getStorage());
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
		socket.handle = static_cast<int>(result);
		return true;
	}
	bool Socket::connect(const Endpoint& endpoint) noexcept
	{
		auto address = reinterpret_cast<const sockaddr*>(
			&endpoint.getStorage());
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
		int size) noexcept
	{
		return ::recv(
			handle,
			static_cast<char*>(buffer),
			size,
			0);
	}
	int Socket::send(
		const void* buffer,
		int size) noexcept
	{
		return ::send(
			handle,
			static_cast<const char*>(buffer),
			size,
			0);
	}

	int Socket::receiveFrom(
		void* buffer,
		int size,
		Endpoint& endpoint) noexcept
	{
		auto address = reinterpret_cast<sockaddr*>(
			&endpoint.getStorage());
		socklen_t length =
			sizeof(sockaddr_storage);

		auto result = ::recvfrom(
			handle,
			static_cast<char*>(buffer),
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
		int size,
		const Endpoint& endpoint) noexcept
	{
		auto address = reinterpret_cast<const sockaddr*>(
			&endpoint.getStorage());

		return ::sendto(
			handle,
			static_cast<const char*>(buffer),
			size,
			0,
			address,
			sizeof(sockaddr_storage));
	}

	bool Socket::shutdown(
		SocketShutdown shutdown) noexcept
	{
		int shutdownType;

#if INJECTOR_SYSTEM_LINUX || INJECTOR_SYSTEM_MACOS
		if(shutdown == SocketShutdown::Receive)
			shutdownType = SHUT_RD;
		else if(shutdown == SocketShutdown::Send)
			shutdownType =  SHUT_WR;
		else if(shutdown == SocketShutdown::Both)
			shutdownType = SHUT_RDWR;
		else
			return false;
#elif INJECTOR_SYSTEM_WINDOWS
		if (shutdown == SocketShutdown::Receive)
			shutdownType = SD_RECEIVE;
		else if (shutdown == SocketShutdown::Send)
			shutdownType = SD_SEND;
		else if (shutdown == SocketShutdown::Both)
			shutdownType = SD_BOTH;
		else
			return false;
#endif

		auto result = ::shutdown(
			handle,
			shutdownType);

		return result == 0;
	}
	bool Socket::close() noexcept
	{
		handle = NULL_SOCKET;

#if INJECTOR_SYSTEM_LINUX || INJECTOR_SYSTEM_MACOS
		return ::close(handle) == 0;
#elif INJECTOR_SYSTEM_WINDOWS
		return ::closesocket(handle) == 0;
#endif
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
