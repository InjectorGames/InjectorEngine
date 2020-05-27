#pragma once
#include <entityx/entityx.h>
#include <asio.hpp>

namespace inject
{
	class NetContextSystem final : public entityx::System<NetContextSystem>
	{
	private:
		std::shared_ptr<asio::io_context> context;
	public:
		NetContextSystem(
			const std::shared_ptr<asio::io_context>& _context =
			std::make_shared<asio::io_context>()) :
			context(_context)
		{}

		void update(entityx::EntityManager& entities,
			entityx::EventManager& events,
			entityx::TimeDelta deltaTime) override
		{
			context->poll();
			context->reset();
		}

		inline const std::shared_ptr<asio::io_context> getContext() const
		{
			return context;
		}
	};
}
