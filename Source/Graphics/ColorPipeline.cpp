#include "Injector/Graphics/ColorPipeline.hpp"
#include "Injector/Graphics/GraphicsException.hpp"

namespace Injector::Graphics
{
	ColorPipeline::~ColorPipeline()
	{}

	const Vector4& ColorPipeline::getColor() const
	{
		throw GraphicsException("Not implemented color pipeline function");
	}
	void ColorPipeline::setColor(const Vector4& _color)
	{
		throw GraphicsException("Not implemented color pipeline function");
	}
}
