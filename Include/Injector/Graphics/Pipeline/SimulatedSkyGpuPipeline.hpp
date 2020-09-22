#pragma once
#include "Injector/Graphics/Pipeline/GpuPipeline.hpp"

namespace Injector
{
	class SimulatedSkyGpuPipeline : public GpuPipeline
	{
	 public:
		virtual ~SimulatedSkyGpuPipeline();

		virtual float getHeight() const;
		virtual void setHeight(float color);
	};
}
