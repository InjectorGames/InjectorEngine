#include "Injector/Graphics/RenderComponent.hpp"

namespace Injector::Graphics
{
	RenderComponent::RenderComponent(
		const shared_ptr<Pipeline>& _pipeline,
		const shared_ptr<Mesh>& _mesh,
		bool _render) :
		pipeline(_pipeline),
		mesh(_mesh),
		render(_render)
	{}
	RenderComponent::~RenderComponent()
	{}
}
