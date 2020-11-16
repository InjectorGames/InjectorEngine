#pragma once
#include "Injector/Graphics/GpuImage.hpp"

namespace Injector
{
	class ColorGpuPipeline
	{
	 public:
		virtual std::shared_ptr<GpuImage> getImage() const = 0;
	};
}
