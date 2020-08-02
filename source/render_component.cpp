#include <injector/render_component.hpp>

namespace INJECTOR_NAMESPACE
{
	RenderComponent::RenderComponent(
		const MaterialHandle& _material,
		const MeshHandle& _mesh,
		bool _ascending,
		int _queue,
		int _offset,
		bool _render) :
		material(_material),
		mesh(_mesh),
		ascending(_ascending),
		queue(_queue),
		offset(_offset),
		render(_render)
	{}
}
