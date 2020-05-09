#pragma once
#include <inject/camera_component.hpp>
#include <inject/aspect_ratio_event.hpp>

#include <entityx/entityx.h>

namespace inject
{
	class CameraSystem final :
		public entityx::System<CameraSystem>,
		public entityx::Receiver<CameraSystem>
	{
	private:
		float newAspectRatio;
	public:
		CameraSystem() :
			newAspectRatio(0.0f)
		{}

		void configure(entityx::EntityManager& entities,
			entityx::EventManager& events) override
		{
			events.subscribe<AspectRatioEvent>(*this);
		}

		void update(entityx::EntityManager& entities,
			entityx::EventManager& events,
			entityx::TimeDelta deltaTime) override
		{
			entities.each<CameraComponent>(
				[](entityx::Entity entity, CameraComponent& cameraComponent)
				{
					if (cameraComponent.viewChanged)
					{
						cameraComponent.viewMatrix =
							glm::scale(glm::mat4(1.0f), -cameraComponent.scale) *
							glm::mat4_cast(glm::normalize(cameraComponent.rotation)) *
							glm::translate(glm::mat4(1.0f), cameraComponent.position);

						cameraComponent.viewChanged = false;
					}
					if (cameraComponent.projChanged)
					{
						if (cameraComponent.type == CameraComponent::Type::Perspective)
						{
							cameraComponent.projMatrix = glm::perspective(
								cameraComponent.fieldOfView, cameraComponent.aspectRatio,
								cameraComponent.clipPlane.x, cameraComponent.clipPlane.y);
						}
						else if (cameraComponent.type == CameraComponent::Type::Orthographic)
						{
							cameraComponent.projMatrix = glm::ortho(
								cameraComponent.frustum.x, cameraComponent.frustum.y,
								cameraComponent.frustum.z, cameraComponent.frustum.w,
								cameraComponent.clipPlane.x, cameraComponent.clipPlane.y);
						}
						else
						{
							throw std::runtime_error("Failed to update camera, unsupported type.");
						}

						cameraComponent.projChanged = false;
					}
				});

			if (newAspectRatio != 0.0f)
			{
				auto aspectRatio = newAspectRatio;
				newAspectRatio = 0.0f;

				entities.each<CameraComponent>([aspectRatio](entityx::Entity entity, CameraComponent& cameraComponent)
					{
						if (cameraComponent.updateAspectRatio)
						{
							cameraComponent.aspectRatio = aspectRatio;
							cameraComponent.projChanged = true;
						}
					});
			}
		}

		void receive(const AspectRatioEvent& event)
		{
			newAspectRatio = event.aspectRatio;
		}
	};
}
