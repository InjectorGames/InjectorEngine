#pragma once
#include "Injector/ECS/EcsSystem.hpp"
#include "Injector/ECS/EcsEntity.hpp"
#include "Injector/Graphics/CameraEcsComponent.hpp"

#include <memory>

namespace Injector
{
	class VrSystem : public EcsSystem
	{
	public:
		std::shared_ptr<EcsEntity> hmd;
		
		void update() override;
	};
}
