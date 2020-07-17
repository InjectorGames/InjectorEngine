#pragma once
#include <inject/defines.hpp>
#include <entityx/entityx.h>
#include <asio.hpp>

namespace INJECT_NAMESPACE
{
	class NetContextSystem final :
		public entityx::System<NetContextSystem>
	{
	public:
		using Context = asio::io_context;
	private:
		std::shared_ptr<Context> context;
	public:
		NetContextSystem(
			const std::shared_ptr<Context>& _context =
			std::make_shared<Context>()) :
			context(_context)
		{}

		void update(entityx::EntityManager& entities,
			entityx::EventManager& events,
			entityx::TimeDelta deltaTime) override
		{
			context->poll();
			context->reset();
		}

		inline const std::shared_ptr<Context> getContext() const
		{
			return context;
		}
	};
}
