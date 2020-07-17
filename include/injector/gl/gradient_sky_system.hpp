#pragma once
#include <inject/gl/gradient_sky_material.hpp>
#include <entityx/entity.h>

// TODO: Use box or sphere instead

namespace INJECT_NAMESPACE
{
	class GlGradientSkySystem : public entityx::System<GlGradientSkySystem>
	{
	public:
		std::shared_ptr<GlGradientSkyMaterial> material;
		glm::vec3* cameraEulerAngles;

		GlGradientSkySystem() :
			material(),
			cameraEulerAngles()
		{}

		void update(entityx::EntityManager& entities,
			entityx::EventManager& events,
			entityx::TimeDelta deltaTime) override
		{
			if (material && cameraEulerAngles)
			{
				material->use();
				material->setPitch(cameraEulerAngles->x);
				material->unuse();
			}
		}
	};
}
