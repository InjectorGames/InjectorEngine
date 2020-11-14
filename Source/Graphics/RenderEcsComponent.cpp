#include "Injector/Graphics/RenderEcsComponent.hpp"

namespace Injector
{
	RenderEcsComponent::RenderEcsComponent(
		const BoundingBox3& _bounds,
		const std::shared_ptr<GpuPipeline>& _pipeline,
		const std::shared_ptr<GpuMesh>& _mesh,
		bool _render) noexcept :
		bounds(_bounds),
		pipeline(_pipeline),
		mesh(_mesh),
		render(_render)
	{
	}
}
