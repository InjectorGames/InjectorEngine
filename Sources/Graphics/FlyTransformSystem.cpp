#include "Injector/Graphics/FlyTransformSystem.hpp"
#include "Injector/Engine.hpp"
#include "Injector/Exception/NullException.hpp"

#include <algorithm>

namespace Injector
{
	FlyTransformSystem::FlyTransformSystem(
		const std::shared_ptr<Window>& _window) :
		window(_window),
		rotating(false),
		eulerAngles(),
		transform(),
		speed(2.0f),
		sensitivity(0.0025f)
	{
		if (!_window)
			throw NullException("FlyTransformSystem", "FlyTransformSystem", "window");
	}
	FlyTransformSystem::~FlyTransformSystem()
	{}

	void FlyTransformSystem::update()
	{
		TransformComponent* transformComponent;

		if (!transform || !transform->getComponent(transformComponent))
			return;

		uint32_t mouseButtons;
		IntVector2 mousePosition;
		window->getMouseState(mousePosition, mouseButtons);

		if (mouseButtons & MouseButton::Right)
		{
			if (!rotating)
			{
				rotating = true;
				window->setMouseMode(true);
			}

			auto deltaTime = static_cast<float>(Engine::getUpdateDeltaTime());
			// TODO: fix side move bug
			auto& translation = window->getTranslation();
			transformComponent->position += 
				transformComponent->rotation * translation * -speed * deltaTime;

			auto& rotation = window->getRotation();
			eulerAngles += rotation * sensitivity;
			eulerAngles.x = std::clamp(eulerAngles.x,
				-Converter::toRadians(89.9f), Converter::toRadians(89.9f));

			transformComponent->rotation = Quaternion(eulerAngles);
			transformComponent->changed = true;
		}
		else
		{
			if (rotating)
			{
				rotating = false;
				window->setMouseMode(false);
			}
		}
	}

	/*void configure(entityx::EntityManager& entities,
		entityx::EventManager& events) override
	{
		events.subscribe<KeyboardEvent>(*this);
		events.subscribe<MouseMotionEvent>(*this);
		events.subscribe<MouseButtonEvent>(*this);

		camera = entities.create();
		camera.assign<PerspCameraComponent>(0);
		camera.assign<TransformComponent>(TransformComponent::Type::Orbit, entityx::Entity(),
			glm::vec3(1.0f), glm::vec3(), glm::quat(glm::vec3()), glm::mat4(), true);
	}

	void update(entityx::EntityManager& entities,
		entityx::EventManager& events,
		entityx::TimeDelta deltaTime) override
	{
		if (camera.valid() && camera.has_component<TransformComponent>())
		{
			auto& transform = *camera.component<TransformComponent>();
			transform.position += translation * transform.rotation *
				speed * static_cast<float>(deltaTime);
			transform.changed = true;

			if (rotating)
			{
				eulerAngles += rotation * sensitivity;

				if (clampPitch)
					eulerAngles.x = std::clamp(eulerAngles.x, -1.57f, 1.57f);

				transform.rotation =
					glm::angleAxis(eulerAngles.x, glm::vec3(1.0f, 0.0f, 0.0f)) *
					glm::angleAxis(eulerAngles.y, glm::vec3(0.0f, 1.0f, 0.0f));
			}
		}

		rotation = glm::vec3(0.0f);
	}

	void receive(const KeyboardEvent& event)
	{
		if (event.data.keysym.scancode == SDL_Scancode::SDL_SCANCODE_A)
		{
			if (event.data.state == KeyboardEvent::State::Released && translation.x > 0.0f)
				translation.x = 0.0f;
			else if (event.data.state == KeyboardEvent::State::Pressed)
				translation.x = 1.0f;
		}
		else if (event.data.keysym.scancode == SDL_Scancode::SDL_SCANCODE_D)
		{
			if (event.data.state == KeyboardEvent::State::Released && translation.x < 0.0f)
				translation.x = 0.0f;
			else if (event.data.state == KeyboardEvent::State::Pressed)
				translation.x = -1.0f;
		}
		else if (event.data.keysym.scancode == SDL_Scancode::SDL_SCANCODE_LCTRL)
		{
			if (event.data.state == KeyboardEvent::State::Released && translation.y > 0.0f)
				translation.y = 0.0f;
			else if (event.data.state == KeyboardEvent::State::Pressed)
				translation.y = 1.0f;
		}
		else if (event.data.keysym.scancode == SDL_Scancode::SDL_SCANCODE_SPACE)
		{
			if (event.data.state == KeyboardEvent::State::Released && translation.y < 0.0f)
				translation.y = 0.0f;
			else if (event.data.state == KeyboardEvent::State::Pressed)
				translation.y = -1.0f;
		}
		else if (event.data.keysym.scancode == SDL_Scancode::SDL_SCANCODE_W)
		{
			if (event.data.state == KeyboardEvent::State::Released && translation.z < 0.0f)
				translation.z = 0.0f;
			else if (event.data.state == KeyboardEvent::State::Pressed)
				translation.z = -1.0f;
		}
		else if (event.data.keysym.scancode == SDL_Scancode::SDL_SCANCODE_S)
		{
			if (event.data.state == KeyboardEvent::State::Released && translation.z > 0.0f)
				translation.z = 0.0f;
			else if (event.data.state == KeyboardEvent::State::Pressed)
				translation.z = 1.0f;
		}
	}
	void receive(const MouseMotionEvent& event)
	{
		rotation += glm::vec3(-event.data.yrel, -event.data.xrel, 0.0f);
	}
	void receive(const MouseButtonEvent& event)
	{
		if (event.data.button == MouseButtonEvent::Button::Right)
		{
			if (event.data.state == MouseButtonEvent::State::Released)
			{
				// TODO: move to engine class
				SDL_SetRelativeMouseMode(SDL_FALSE);
				rotating = false;
			}
			else if (event.data.state == MouseButtonEvent::State::Pressed)
			{
				SDL_SetRelativeMouseMode(SDL_TRUE);
				rotating = true;
			}
		}
	}

	inline entityx::Entity getCamera()
	{
		return camera;
	}
	inline const glm::vec3& getEulerAngles()
	{
		return eulerAngles;
	}*/
}
