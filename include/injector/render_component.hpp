#pragma once
#include <injector/component.hpp>
#include <injector/graphics/mesh.hpp>
#include <injector/graphics/material.hpp>

namespace INJECTOR_NAMESPACE
{
	struct RenderComponent final : public Component
	{
		MaterialHandle material;
		MeshHandle mesh;
		bool ascending;
		int queue;
		int offset;
		bool render;

		RenderComponent(
			const MaterialHandle& material = nullptr,
			const MeshHandle& mesh = nullptr,
			bool ascending = true,
			int queue = 0,
			int offset = 0,
			bool render = true);
	};
}
