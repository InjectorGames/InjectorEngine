#include "Injector/Network/NetContextSystem.hpp"

namespace Injector
{
	NetContextSystem::NetContextSystem(
		const std::shared_ptr<asio::io_context>& _context) :
		context(_context)
	{
	}

	void NetContextSystem::update()
	{
		context->poll();
		context->reset();
	}

	std::shared_ptr<asio::io_context>
	    NetContextSystem::getContext() const noexcept
	{
		return context;
	}
}
