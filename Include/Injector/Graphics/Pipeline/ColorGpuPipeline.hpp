#pragma once
#include "Injector/Mathematics/Vector4.hpp"

namespace Injector
{
	class ColorGpuPipeline
	{
	 public:
		virtual const FloatVector4& getColor() const = 0;
		virtual void setColor(const FloatVector4& color) = 0;
	};
}
