#pragma once
#include <injector/quaternion.hpp>

namespace INJECTOR_NAMESPACE
{
	struct RotateComponent
	{
		Quaternion rotation;
		RotateComponent(const Quaternion& rotation);
	};
}