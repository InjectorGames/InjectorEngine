#pragma once
#include "Injector/ECS/EcsComponent.hpp"
#include "Injector/Graphics/GpuMesh.hpp"
#include "Injector/Graphics/GpuPipeline.hpp"
#include "Injector/Mathematics/BoundingBox3.hpp"

#include <memory>

namespace Injector
{
	struct RenderEcsComponent final : public EcsComponent
	{
		BoundingBox3 bounds;
		std::shared_ptr<GpuPipeline> pipeline;
		std::shared_ptr<GpuMesh> mesh;
		bool render;

		explicit RenderEcsComponent(
			const BoundingBox3& bounds = BoundingBox3::one,
			const std::shared_ptr<GpuPipeline>& pipeline = nullptr,
			const std::shared_ptr<GpuMesh>& mesh = nullptr,
			bool render = true) noexcept;
	};
}
