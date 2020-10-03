#pragma once
#include "Injector/Network/Endpoint.hpp"
#include "Injector/Network/SocketType.hpp"
#include "Injector/Network/SocketFamily.hpp"
#include "Injector/Network/SocketShutdown.hpp"

namespace Injector
{
	class Socket
	{
	 protected:
		SocketFamily family;
		SocketType type;
		uint64_t handle;
	 public:
		Socket(
			SocketFamily family,
			SocketType type);
		virtual ~Socket();

		bool shutdown(
			SocketShutdown shutdown) noexcept;
		bool close() noexcept;
	};
}
