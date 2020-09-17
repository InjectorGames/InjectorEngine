#pragma once
#include "Injector/Component.hpp"
#include "Injector/Graphics/Mesh.hpp"
#include "Injector/Graphics/Pipeline.hpp"

#include <memory>

namespace Injector
{
	struct RenderComponent : public Component
	{
		std::shared_ptr<Pipeline> pipeline;
		std::shared_ptr<Mesh> mesh;
		bool render;

		RenderComponent(
			const std::shared_ptr<Pipeline>& pipeline = nullptr,
			const std::shared_ptr<Mesh>& mesh = nullptr,
			bool render = true);
		virtual ~RenderComponent();
	};
}
