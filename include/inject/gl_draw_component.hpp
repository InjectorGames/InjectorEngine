#pragma once
#include <inject/gl_mesh.hpp>
#include <inject/gl_material.hpp>

#include <entityx/entityx.h>

namespace inject
{
	struct GlDrawComponent final : public entityx::Component<GlDrawComponent>
	{
		std::shared_ptr<GlMaterial> material;
		std::shared_ptr<GlMesh> mesh;
		bool draw;

		GlDrawComponent(const std::shared_ptr<GlMaterial>& _material = {}, const std::shared_ptr<GlMesh>& _mesh = {}, const bool _draw = true) :
			material(_material),
			mesh(_mesh),
			draw(_draw)
		{}
	};
}