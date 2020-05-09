#pragma once
#include <inject/camera_component.hpp>
#include <inject/mouse_button_event.hpp>
#include <inject/transform_component.hpp>


#include <entityx/entityx.h>
#include <glm/glm.hpp>

namespace inject
{
	class FirstPersonSystem final :
		public entityx::System<FirstPersonSystem>,
		public entityx::Receiver<FirstPersonSystem>
	{
	private:
		entityx::Entity camera;
		bool overviewing;
		glm::vec3 overview;
	public:
		float sensitivity;

		FirstPersonSystem() :
			camera(),
			overviewing(false),
			overview(glm::vec3(0.0f)),
			sensitivity(0.15f)
		{}

		void configure(entityx::EntityManager& entities, entityx::EventManager& events) override
		{
			events.subscribe<MouseButtonEvent>(*this);
			events.subscribe<MouseMotionEvent>(*this);

			camera = entities.create();
			camera.assign<CameraComponent>();
			camera.assign<TransformComponent>(glm::vec3(-1.0f), glm::vec3(0.0f, 0.0f, 2.0f));
		}

		void update(entityx::EntityManager& entities,
			entityx::EventManager& events,
			entityx::TimeDelta deltaTime) override
		{
			if (overviewing && camera.has_component<TransformComponent>())
			{
				auto& transformComponent = *camera.component<TransformComponent>();
				transformComponent.rotation *= glm::quat(overview * sensitivity * static_cast<float>(deltaTime));
				transformComponent.changed = true;
			}

			overview = glm::vec3(0.0f);
		}

		void receive(const MouseButtonEvent& event)
		{
			if (event.button == MouseButtonEvent::Button::Right)
			{
				if (event.state == MouseButtonEvent::State::Pressed)
				{
					SDL_SetRelativeMouseMode(SDL_TRUE);
					overviewing = true;
				}
				else if (event.state == MouseButtonEvent::State::Released)
				{
					SDL_SetRelativeMouseMode(SDL_FALSE);
					overviewing = false;
				}
			}
		}
		void receive(const MouseMotionEvent& event)
		{
			overview += glm::vec3(
				event.deltaPosition.y,
				event.deltaPosition.x,
				0.0f);
		}
	};
}