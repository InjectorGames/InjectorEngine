#pragma once
#include <inject/aspect_ratio_event.hpp>
#include <inject/persp_camera_component.hpp>
#include <inject/ortho_camera_component.hpp>

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
			newAspectRatio()
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
			entities.each<PerspCameraComponent>(
				[](entityx::Entity entity, PerspCameraComponent& camera)
				{
					if (camera.changed)
					{
						camera.matrix = glm::perspective(
							camera.fieldOfView, camera.aspectRatio,
							camera.clipPlane.x, camera.clipPlane.y);
						camera.changed = false;
					}
				});

			entities.each<OrthoCameraComponent>(
				[](entityx::Entity entity, OrthoCameraComponent& camera)
				{
					if (camera.changed)
					{
						camera.matrix = glm::ortho(
							camera.frustum.x, camera.frustum.y,
							camera.frustum.z, camera.frustum.w,
							camera.clipPlane.x, camera.clipPlane.y);
						camera.changed = false;
					}
				});

			if (newAspectRatio != 0.0f)
			{
				auto aspectRatio = newAspectRatio;
				newAspectRatio = 0.0f;

				entities.each<PerspCameraComponent>(
					[aspectRatio](entityx::Entity entity, PerspCameraComponent& camera)
					{
						if (camera.updateAspectRatio)
						{
							camera.aspectRatio = aspectRatio;
							camera.changed = true;
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
