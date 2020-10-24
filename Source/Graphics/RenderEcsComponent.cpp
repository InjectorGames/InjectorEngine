#include "Injector/Graphics/RenderEcsComponent.hpp"

namespace Injector
{
	RenderEcsComponent::RenderEcsComponent(
		const std::shared_ptr<GpuPipeline>& _pipeline,
		const std::shared_ptr<GpuMesh>& _mesh,
		bool _render) :
		pipeline(_pipeline),
		mesh(_mesh),
		render(_render)
	{
	}
}
