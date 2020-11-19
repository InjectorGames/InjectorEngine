#pragma once
#include "Injector/Graphics/Pipeline/ColorGpuPipeline.hpp"
#include "Injector/Graphics/Pipeline/ImageGpuPipeline.hpp"

namespace Injector
{
	class ImageColorGpuPipeline :
		public ColorGpuPipeline,
		public ImageGpuPipeline
	{
	};
}
