#pragma once
#include "Injector/Graphics/Pipeline/DiffuseGpuPipeline.hpp"
#include "Injector/Graphics/Pipeline/ImageGpuPipeline.hpp"

namespace Injector
{
	class ImageDiffuseGpuPipeline :
		public DiffuseGpuPipeline,
		public ImageGpuPipeline
	{
	};
}
