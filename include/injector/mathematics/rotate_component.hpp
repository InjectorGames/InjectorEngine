#pragma once
#include <injector/component.hpp>
#include <injector/mathematics/quaternion.hpp>

namespace INJECTOR_NAMESPACE
{
	struct RotateComponent : public Component
	{
		Quaternion rotation;

		RotateComponent(const Quaternion& rotation);
		virtual ~RotateComponent();
	};
}