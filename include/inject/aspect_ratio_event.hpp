#pragma once
#include <entityx/entityx.h>

namespace inject
{
	struct AspectRatioEvent final : public entityx::Event<AspectRatioEvent>
	{
		float aspectRatio;
		float deltaAspectRatio;

		AspectRatioEvent(const float _aspectRatio, const float _deltaAspectRatio) :
			aspectRatio(_aspectRatio),
			deltaAspectRatio(_deltaAspectRatio)
		{}
	};
}
