#pragma once
#include <injector/vector3.hpp>
#include <injector/matrix4.hpp>
#include <injector/quaternion.hpp>

namespace INJECTOR_NAMESPACE
{
	struct TransformComponent
	{
		enum class Type
		{
			Spin,
			Orbit,
		};

		Type type;
		size_t parent;
		Vector3 scale;
		Vector3 position;
		Quaternion rotation;
		Matrix4 matrix;
		bool changed;

		TransformComponent(
			Type _type = Type::Spin,
			size_t _parent = 0,
			const Vector3& _scale = Vector3::one,
			const Vector3& _position = Vector3::zero,
			const Quaternion& _rotation = Quaternion(Vector3::zero),
			const Matrix4& _matrix = Matrix4::one,
			const bool _changed = true) :
			type(_type),
			parent(_parent),
			scale(_scale),
			position(_position),
			rotation(_rotation),
			matrix(_matrix),
			changed(_changed)
		{}
	};
}
