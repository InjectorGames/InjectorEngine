#include "Injector/Graphics/RenderComponent.hpp"

namespace Injector
{
	RenderComponent::RenderComponent(
		const std::shared_ptr<Pipeline>& _pipeline,
		const std::shared_ptr<Mesh>& _mesh,
		bool _render) :
		pipeline(_pipeline),
		mesh(_mesh),
		render(_render)
	{}
	RenderComponent::~RenderComponent()
	{}
}
