#include <injector/graphics/color_pipeline.hpp>

namespace INJECTOR_NAMESPACE
{
	ColorPipeline::ColorPipeline(const Vector4& _color) :
		color(_color)
	{}
	ColorPipeline::~ColorPipeline()
	{}

	const Vector4& ColorPipeline::getColor() const noexcept
	{
		return color;
	}
	void ColorPipeline::setColor(const Vector4& _color) noexcept
	{
		color = Vector4(_color);
	}
}
