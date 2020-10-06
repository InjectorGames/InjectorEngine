#pragma once

namespace Injector
{
	enum class SocketShutdown : int
	{
		Receive = 0,
		Send = 1,
		Both = 2,
	};
}
