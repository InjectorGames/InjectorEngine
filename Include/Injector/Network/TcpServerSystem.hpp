#pragma once
#include "Injector/System.hpp"
#include "Injector/Network/Socket.hpp"

namespace Injector
{
	class TcpServerSystem : public System
	{
	 protected:
		Socket socket;
	 public:
		TcpServerSystem();
	};
}