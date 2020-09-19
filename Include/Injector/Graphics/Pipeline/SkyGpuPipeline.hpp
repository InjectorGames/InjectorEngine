#pragma once
#include "Injector/Graphics/Pipeline/GpuPipeline.hpp"

namespace Injector
{
	class SkyGpuPipeline : public GpuPipeline
	{
	 public:
		virtual ~SkyGpuPipeline();

		virtual float getHeight() const;
		virtual void setHeight(float color);
	};
}
