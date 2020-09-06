#pragma once
#include "Injector/Component.hpp"
#include "Injector/Mathematics/Quaternion.hpp"

namespace Injector::Mathematics
{
	struct RotateComponent : public Component
	{
		Quaternion rotation;

		RotateComponent(const Quaternion& rotation);
		virtual ~RotateComponent();
	};
}