#include "Injector/Graphics/ColorGpuPipeline.hpp"
#include "Injector/Exception/NotImplementedException.hpp"

namespace Injector
{
	ColorGpuPipeline::~ColorGpuPipeline()
	{}

	const Vector4& ColorGpuPipeline::getColor() const
	{
		throw NotImplementedException("ColorGpuPipeline", "getColor");
	}
	void ColorGpuPipeline::setColor(const Vector4& _color)
	{
		throw NotImplementedException("ColorGpuPipeline", "setColor");
	}
}
