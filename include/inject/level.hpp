#pragma once
#include <entityx/entityx.h>

#include <cstdio>

namespace inject
{
	class Level : public entityx::EntityX
	{
	protected:
		uint32_t id;
	public:
		Level(const uint32_t _id) :
			id(_id)
		{}

		inline uint32_t getId() const noexcept
		{
			return id;
		}

		inline void update(const double deltaTime)
		{
			systems.update_all(static_cast<entityx::TimeDelta>(deltaTime));
		}
	};
}
