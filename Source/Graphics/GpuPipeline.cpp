#include "Injector/Graphics/GpuPipeline.hpp"

namespace Injector
{
	GpuPipeline::GpuPipeline(
		GpuDrawMode _drawMode) :
		drawMode(_drawMode)
	{
	}

	GpuDrawMode GpuPipeline::getDrawMode() const noexcept
	{
		return drawMode;
	}
}
