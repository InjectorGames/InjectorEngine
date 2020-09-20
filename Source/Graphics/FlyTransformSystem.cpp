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
		lastMousePosition(),
		transform(),
		speed(2.0f),
		sensitivity(0.0025f)
	{
		if (!_window)
		{
			throw NullException(
				"FlyTransformSystem",
				"FlyTransformSystem",
				"window");
		}
	}
	FlyTransformSystem::~FlyTransformSystem()
	{
	}

	void FlyTransformSystem::update()
	{
		TransformComponent* transformComponent;

		if (!transform || !transform->getComponent(transformComponent))
			return;

		if (window->getMouseButton(MouseButton::Right) == ButtonState::Press)
		{
			if (!rotating)
			{
				rotating = true;
				window->setMouseMode(MouseMode::Disabled);
			}

			auto mousePosition = window->getMousePosition();
			auto deltaMousePosition = mousePosition - lastMousePosition;
			lastMousePosition = mousePosition;

			eulerAngles += Vector3(
				deltaMousePosition.y * sensitivity,
				deltaMousePosition.x * sensitivity,
				0.0f);
			eulerAngles.x = std::clamp(eulerAngles.x,
				-Converter::toRadians(89.9f),
				Converter::toRadians(89.9f));
			transformComponent->rotation = Quaternion(eulerAngles);

			auto translation = Vector3();

			if (window->getKeyboardButton(KeyboardButton::A) == ButtonState::Press)
				translation.x = -1.0f;
			else if (window->getKeyboardButton(KeyboardButton::D) == ButtonState::Press)
				translation.x = 1.0f;

			if (window->getKeyboardButton(KeyboardButton::LeftControl) == ButtonState::Press)
				translation.y = -1.0f;
			else if (window->getKeyboardButton(KeyboardButton::Space) == ButtonState::Press)
				translation.y = 1.0f;

			if (window->getKeyboardButton(KeyboardButton::S) == ButtonState::Press)
				translation.z = -1.0f;
			else if (window->getKeyboardButton(KeyboardButton::W) == ButtonState::Press)
				translation.z = 1.0f;

			auto deltaTime = static_cast<float>(Engine::getUpdateDeltaTime());

			transformComponent->position +=
				transformComponent->rotation * translation * -speed * deltaTime;
		}
		else
		{
			if (rotating)
			{
				rotating = false;
				window->setMouseMode(MouseMode::Normal);
			}

			lastMousePosition = window->getMousePosition();
		}
	}
}
