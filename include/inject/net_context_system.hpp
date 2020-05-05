#pragma once
#include <entityx/entityx.h>
#include <asio.hpp>

namespace njng
{
	class NetContextSystem final : public entityx::System<NetContextSystem>
	{
	private:
		asio::io_context m_context;
	public:
		NetContextSystem() :
			m_context()
		{}

		inline asio::io_context& context()
		{
			return m_context;
		}

		void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override
		{
			m_context.poll();
			m_context.reset();
		}
	};
}
