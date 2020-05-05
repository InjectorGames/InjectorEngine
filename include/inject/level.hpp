#pragma once
#include <entityx/entityx.h>

namespace njng
{
	class Level : public entityx::EntityX
	{
	protected:
		inline void configureSystems()
		{
			systems.configure();
		}
	public:
		const size_t id;

		Level(const size_t _id) :
			id(_id)
		{}
	};
}
