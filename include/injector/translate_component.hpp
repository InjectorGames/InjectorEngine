#pragma once
#include <injector/component.hpp>
#include <injector/mathematics/vector3.hpp>

namespace INJECTOR_NAMESPACE
{
	struct TranslateComponent final : public Component
	{
		Vector3 translation;
		TranslateComponent(const Vector3& translation);
	};
}