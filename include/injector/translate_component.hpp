#pragma once
#include <injector/mathematics/vector3.hpp>

namespace INJECTOR_NAMESPACE
{
	struct TranslateComponent
	{
		Vector3 translation;
		TranslateComponent(const Vector3& translation);
	};
}