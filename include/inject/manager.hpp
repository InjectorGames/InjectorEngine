#pragma once
#include <entityx/entityx.h>
#include <SDL_events.h>

namespace inject
{
	class Manager : public entityx::EntityX
	{
	protected:
		uint32_t id;
		bool isActive;
	public:
		Manager(const uint32_t _id = 0,
			const bool _isActive = true) :
			id(_id),
			isActive(_isActive)
		{}

		inline const uint32_t getID() const noexcept
		{
			return id;
		}
		inline const bool getActive() const noexcept
		{
			return isActive;
		}

		virtual void handleEvent(const SDL_Event& event)
		{
			return;
		}
		virtual void update(const double deltaTime)
		{
			systems.update_all(static_cast<entityx::TimeDelta>(deltaTime));
		}
	};
}