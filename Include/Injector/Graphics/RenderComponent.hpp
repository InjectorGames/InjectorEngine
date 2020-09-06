#pragma once
#include "Injector/Component.hpp"
#include "Injector/Graphics/Mesh.hpp"
#include "Injector/Graphics/Pipeline.hpp"

#include <memory>

namespace Injector::Graphics
{
	using namespace std;

	struct RenderComponent : public Component
	{
		shared_ptr<Pipeline> pipeline;
		shared_ptr<Mesh> mesh;
		bool render;

		RenderComponent(
			const shared_ptr<Pipeline>& pipeline = nullptr,
			const shared_ptr<Mesh>& mesh = nullptr,
			bool render = true);
		virtual ~RenderComponent();
	};
}
