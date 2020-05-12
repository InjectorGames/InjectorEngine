#pragma once
#include <entityx/entityx.h>
#include <asio.hpp>

namespace inject
{
	class NetContextSystem final : public entityx::System<NetContextSystem>
	{
	private:
		asio::io_context context;
	public:
		NetContextSystem() :
			context()
		{}

		void update(entityx::EntityManager& entities,
			entityx::EventManager& events,
			entityx::TimeDelta deltaTime) override
		{
			context.poll();
			context.reset();
		}

		inline asio::io_context& getContext()
		{
			return context;
		}
	};
}
