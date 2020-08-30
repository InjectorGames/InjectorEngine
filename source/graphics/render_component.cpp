#include <injector/graphics/render_component.hpp>

namespace INJECTOR_NAMESPACE
{
	RenderComponent::RenderComponent(
		const PipelineHandle& _pipeline,
		const MeshHandle& _mesh,
		bool _render) :
		pipeline(_pipeline),
		mesh(_mesh),
		render(_render)
	{}
	RenderComponent::~RenderComponent()
	{}
}
