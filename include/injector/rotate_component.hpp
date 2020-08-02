#pragma once
#include <injector/mathematics/quaternion.hpp>

namespace INJECTOR_NAMESPACE
{
	struct RotateComponent
	{
		Quaternion rotation;
		RotateComponent(const Quaternion& rotation);
	};
}