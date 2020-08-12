#include <injector/mathematics/rotate_component.hpp>

namespace INJECTOR_NAMESPACE
{
	RotateComponent::RotateComponent(
		const Quaternion& _rotation) :
		rotation(_rotation)
	{}
	RotateComponent::~RotateComponent()
	{}
}
