#pragma once

namespace Injector
{
	class SimulatedSkyGpuPipeline
	{
	 public:
		virtual float getHeight() const = 0;
		virtual void setHeight(float color) = 0;
	};
}
