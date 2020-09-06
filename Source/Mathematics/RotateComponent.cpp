#include "Injector/Mathematics/RotateComponent.hpp"

namespace Injector::Mathematics
{
	RotateComponent::RotateComponent(
		const Quaternion& _rotation) :
		rotation(_rotation)
	{}
	RotateComponent::~RotateComponent()
	{}
}
