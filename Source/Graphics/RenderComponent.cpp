#include "Injector/Graphics/RenderComponent.hpp"

namespace Injector
{
	RenderComponent::RenderComponent(
		const std::shared_ptr<GpuPipeline>& _pipeline,
		const std::shared_ptr<GpuMesh>& _mesh,
		bool _render) :
		pipeline(_pipeline),
		mesh(_mesh),
		render(_render)
	{}
	RenderComponent::~RenderComponent()
	{}
}
