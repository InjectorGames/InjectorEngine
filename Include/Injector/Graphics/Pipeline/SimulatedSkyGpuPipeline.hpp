#pragma once
#include "Injector/Graphics/Pipeline/GpuPipeline.hpp"

namespace Injector
{
	class SimulatedSkyGpuPipeline : public GpuPipeline
	{
	 public:
		virtual float getHeight() const = 0;
		virtual void setHeight(float color) = 0;
	};
}
