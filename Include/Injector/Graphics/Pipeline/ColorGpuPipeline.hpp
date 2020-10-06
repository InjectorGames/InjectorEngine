#pragma once
#include "Injector/Graphics/GpuPipeline.hpp"

namespace Injector
{
	class ColorGpuPipeline : public GpuPipeline
	{
	 public:
		virtual const Vector4& getColor() const = 0;
		virtual void setColor(const Vector4& color) = 0;
	};
}
