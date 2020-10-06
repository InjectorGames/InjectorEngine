#pragma once
#include "Injector/ECS/Component.hpp"
#include "Injector/Graphics/GpuMesh.hpp"
#include "Injector/Graphics/GpuPipeline.hpp"

#include <memory>

namespace Injector
{
	struct RenderComponent : public Component
	{
		std::shared_ptr<GpuPipeline> pipeline;
		std::shared_ptr<GpuMesh> mesh;
		bool render;

		RenderComponent(
			const std::shared_ptr<GpuPipeline>& pipeline = nullptr,
			const std::shared_ptr<GpuMesh>& mesh = nullptr,
			bool render = true);
	};
}
