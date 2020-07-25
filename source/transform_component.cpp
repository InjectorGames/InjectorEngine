#include <injector/transform_component.hpp>

namespace INJECTOR_NAMESPACE
{
	TransformComponent::TransformComponent(
		const EntityHandle& _parent,
		const Vector3& _position,
		const Quaternion& _rotation,
		const Vector3& _scale,
		Type _type,
		const Matrix4& _matrix,
		const bool _changed) :
		parent(_parent),
		position(_position),
		rotation(_rotation),
		scale(_scale),
		type(_type),
		matrix(_matrix),
		changed(_changed)
	{}
}
