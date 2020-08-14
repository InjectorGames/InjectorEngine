#include <injector/graphics/render_component.hpp>

namespace INJECTOR_NAMESPACE
{
	RenderComponent::RenderComponent(
		const PipelineHandle& _pipeline,
		const MeshHandle& _mesh,
		bool _ascending,
		int _queue,
		int _offset,
		bool _render) :
		pipeline(_pipeline),
		mesh(_mesh),
		ascending(_ascending),
		queue(_queue),
		offset(_offset),
		render(_render)
	{}
	RenderComponent::~RenderComponent()
	{}
}