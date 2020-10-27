#include "Injector/Graphics/GUI/GuiEcsComponent.hpp"

namespace Injector
{
	GuiEcsComponent::GuiEcsComponent(
		const Vector3& _position,
		const Quaternion& _rotation,
		const Vector3& _scale,
		GuiAnchorType _anchor,
		bool _fixedScale,
		const std::shared_ptr<GuiHandler>& _handler) :
		position(_position),
		rotation(_rotation),
		scale(_scale),
		anchor(_anchor),
		fixedScale(_fixedScale),
		handler(_handler)
	{
	}
}
