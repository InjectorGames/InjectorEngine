#pragma once
#include <entityx/entityx.h>

namespace njng
{
	/*class CameraSystem final : public entityx::System<CameraSystem>, public entityx::Receiver<CameraSystem>
	{
	private:
		Window* window;
	public:
		CameraSystem(Window* _window) :
			window(_window)
		{}

		void configure(ecs::EntityManager& entities, ecs::EventManager& events) override
		{
			events.subscribe<AspectRatioEvent>(*this);
		}

		void update(ecs::EntityManager& entities, ecs::EventManager& events, ecs::TimeDelta deltaTime) override
		{
			entities.each<CameraComponent>([](ecs::Entity entity, CameraComponent& cameraComponent)
				{
					if (cameraComponent.isMatrixChanged)
					{
						if (cameraComponent.type == CameraType::Perspective)
						{
							cameraComponent.matrix = glm::perspective(cameraComponent.fieldOfView, cameraComponent.aspectRatio,
								cameraComponent.clipPlane.x, cameraComponent.clipPlane.y);
						}
						else if (cameraComponent.type == CameraType::Orthographic)
						{
							cameraComponent.matrix = glm::ortho(cameraComponent.frustum.x, cameraComponent.frustum.y, cameraComponent.frustum.z, cameraComponent.frustum.w,
								cameraComponent.clipPlane.x, cameraComponent.clipPlane.y);
						}
						else
						{
							throw std::runtime_error("Failed to update camera: unsupported type.");
						}

						cameraComponent.isMatrixChanged = false;
					}
				});
		}

		void receive(const AspectRatioEvent& event)
		{
			auto entities = window->GetEntities();
			auto aspectRatio = event.aspectRatio;

			entities->each<CameraComponent>([aspectRatio](ecs::Entity entity, CameraComponent& cameraComponent)
				{
					if (cameraComponent.updateAspectRatio)
					{
						cameraComponent.aspectRatio = aspectRatio;
						cameraComponent.isMatrixChanged = true;
					}
				});
		}
	};*/
}
