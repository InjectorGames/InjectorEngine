#pragma once
#include "Injector/Graphics/GpuPipeline.hpp"

namespace Injector
{
	class SimulatedSkyGpuPipeline : public GpuPipeline
	{
	 public:
		virtual float getHeight() const = 0;
		virtual void setHeight(float color) = 0;
	};
}
