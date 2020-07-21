#pragma once
#include <injector/vector3.hpp>

namespace INJECTOR_NAMESPACE
{
	struct RotateComponent
	{
		Vector3 rotation;
		RotateComponent(const Vector3& rotation);
	};
}