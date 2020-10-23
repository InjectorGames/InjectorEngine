#pragma once
#include "Injector/Mathematics/Vector/Vector4.hpp"

namespace Injector
{
	class ColorGpuPipeline
	{
	 public:
		virtual const Vector4& getColor() const = 0;
		virtual void setColor(const Vector4& color) = 0;
	};
}
