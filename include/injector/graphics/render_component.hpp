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
		bool ascending;
		int queue;
		int offset;
		bool render;

		RenderComponent(
			const PipelineHandle& pipeline = nullptr,
			const MeshHandle& mesh = nullptr,
			bool ascending = true,
			int queue = 0,
			int offset = 0,
			bool render = true);
		virtual ~RenderComponent();
	};
}
