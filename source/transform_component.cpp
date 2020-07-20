#include <injector/transform_component.hpp>

namespace INJECTOR_NAMESPACE
{
	TransformComponent::TransformComponent(
		Type _type, 
		const EntityHandle& _parent,
		const Vector3& _scale,
		const Vector3& _position,
		const Quaternion& _rotation,
		const Matrix4& _matrix,
		const bool _changed) :
		type(_type),
		parent(_parent),
		scale(_scale),
		position(_position),
		rotation(_rotation),
		matrix(_matrix),
		changed(_changed)
	{}
}
