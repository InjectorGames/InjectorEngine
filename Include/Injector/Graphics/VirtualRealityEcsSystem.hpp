#pragma once
#include "Injector/ECS/EcsSystem.hpp"
#include "Injector/Graphics/CameraEcsComponent.hpp"

#include <memory>

namespace Injector
{
	class VirtualRealityEcsSystem : public EcsSystem
	{
	public:
		std::shared_ptr<EcsEntity> hmd;
		
		void onUpdate() override;
	};
}
