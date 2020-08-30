#pragma once
#include <injector/component.hpp>
#include <injector/graphics/mesh.hpp>
#include <injector/graphics/pipeline.hpp>

namespace INJECTOR_NAMESPACE
{
	struct RenderComponent : public Component
	{
		PipelineHandle pipeline;
		MeshHandle mesh;
		bool render;

		RenderComponent(
			const PipelineHandle& pipeline = nullptr,
			const MeshHandle& mesh = nullptr,
			bool render = true);
		virtual ~RenderComponent();
	};
}
