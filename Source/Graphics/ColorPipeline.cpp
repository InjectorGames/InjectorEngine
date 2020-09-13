#include "Injector/Graphics/ColorPipeline.hpp"
#include "Injector/Exception/NotImplementedException.hpp"

namespace Injector
{
	ColorPipeline::~ColorPipeline()
	{}

	const Vector4& ColorPipeline::getColor() const
	{
		throw NotImplementedException("ColorPipeline", "getColor");
	}
	void ColorPipeline::setColor(const Vector4& _color)
	{
		throw NotImplementedException("ColorPipeline", "setColor");
	}
}
