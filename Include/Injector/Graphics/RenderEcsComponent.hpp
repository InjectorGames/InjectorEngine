#pragma once
#include "Injector/ECS/EcsComponent.hpp"
#include "Injector/Graphics/GpuMesh.hpp"
#include "Injector/Graphics/GpuPipeline.hpp"

#include <memory>

namespace Injector
{
	struct RenderEcsComponent final : public EcsComponent
	{
		std::shared_ptr<GpuPipeline> pipeline;
		std::shared_ptr<GpuMesh> mesh;
		bool render;

		RenderEcsComponent(
			const std::shared_ptr<GpuPipeline>& pipeline = nullptr,
			const std::shared_ptr<GpuMesh>& mesh = nullptr,
			bool render = true);
	};
}
