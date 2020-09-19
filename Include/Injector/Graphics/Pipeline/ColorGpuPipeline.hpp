#pragma once
#include "Injector/Graphics/Pipeline/GpuPipeline.hpp"

namespace Injector
{
	class ColorGpuPipeline : public GpuPipeline
	{
	 public:
		virtual ~ColorGpuPipeline();

		virtual const Vector4& getColor() const;
		virtual void setColor(const Vector4& color);
	};
}
