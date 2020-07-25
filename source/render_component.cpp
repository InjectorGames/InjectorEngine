#include <injector/render_component.hpp>

namespace INJECTOR_NAMESPACE
{
	RenderComponent::RenderComponent(
		Order _order,
		int _queue,
		int _offset,
		const MaterialHandle& _material,
		bool _render) :
		order(_order),
		queue(_queue),
		offset(_offset),
		material(_material),
		render(_render)
	{}
}
