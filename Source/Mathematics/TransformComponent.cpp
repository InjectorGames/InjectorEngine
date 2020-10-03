#include "Injector/Mathematics/TransformComponent.hpp"

namespace Injector
{
	TransformComponent::TransformComponent(
		const Vector3& _position,
		const Quaternion& _rotation,
		const Vector3& _scale,
		RotationOrigin _origin,
		const Matrix4& _matrix,
		const std::shared_ptr<Entity>& _parent) noexcept :
		position(_position),
		rotation(_rotation),
		scale(_scale),
		origin(_origin),
		matrix(_matrix),
		parent(_parent)
	{
	}
}
