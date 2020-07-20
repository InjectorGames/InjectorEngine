#pragma once
#include <injector/entity.hpp>
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
		EntityHandle parent;
		Vector3 scale;
		Vector3 position;
		Quaternion rotation;
		Matrix4 matrix;
		bool changed;

		TransformComponent(
			Type type = Type::Spin,
			const EntityHandle& parent = {},
			const Vector3& scale = Vector3::one,
			const Vector3& position = Vector3::zero,
			const Quaternion& rotation = Quaternion(Vector3::zero),
			const Matrix4& matrix = Matrix4::one,
			const bool changed = true);
	};
}
