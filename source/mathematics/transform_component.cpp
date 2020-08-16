#include <injector/mathematics/transform_component.hpp>

namespace INJECTOR_NAMESPACE
{
	TransformComponent::TransformComponent(
		const Vector3& _position,
		const Quaternion& _rotation,
		const Vector3& _scale,
		RotationOrigin _origin,
		const Matrix4& _matrix,
		const bool _changed) :
		position(_position),
		rotation(_rotation),
		scale(_scale),
		origin(_origin),
		matrix(_matrix),
		changed(_changed)
	{}
	TransformComponent::~TransformComponent()
	{}
}
