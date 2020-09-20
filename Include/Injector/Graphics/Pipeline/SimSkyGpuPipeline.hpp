#pragma once
#include "Injector/Graphics/Pipeline/GpuPipeline.hpp"

namespace Injector
{
	class SimSkyGpuPipeline : public GpuPipeline
	{
	 public:
		virtual ~SimSkyGpuPipeline();

		virtual float getHeight() const;
		virtual void setHeight(float color);
	};
}
