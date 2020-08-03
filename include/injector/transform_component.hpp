#pragma once
#include <injector/component.hpp>
#include <injector/entity.hpp>
#include <injector/mathematics/vector3.hpp>
#include <injector/mathematics/matrix4.hpp>
#include <injector/mathematics/quaternion.hpp>

namespace INJECTOR_NAMESPACE
{
	struct TransformComponent final : public Component
	{
		enum class Type
		{
			Spin,
			Orbit,
		};

		EntityHandle parent;
		Vector3 position;
		Quaternion rotation;
		Vector3 scale;
		Type type;
		Matrix4 matrix;
		bool changed;

		TransformComponent(
			const EntityHandle& parent = nullptr,
			const Vector3& position = Vector3::zero,
			const Quaternion& rotation = Quaternion(Vector3::zero),
			const Vector3& scale = Vector3::one,
			Type type = Type::Spin,
			const Matrix4& matrix = Matrix4::identity,
			const bool changed = true);
	};
}
