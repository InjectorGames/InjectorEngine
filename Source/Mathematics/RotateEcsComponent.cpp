#include "Injector/Mathematics/RotateEcsComponent.hpp"

namespace Injector
{
	RotateEcsComponent::RotateEcsComponent(
		const Quaternion& _rotation) noexcept :
		rotation(_rotation)
	{
	}
}
