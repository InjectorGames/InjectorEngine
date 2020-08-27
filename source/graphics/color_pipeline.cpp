#include <injector/graphics/color_pipeline.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	ColorPipeline::~ColorPipeline()
	{}

	const Vector4& ColorPipeline::getColor() const
	{
		throw std::runtime_error("Not implemented color pipeline function");
	}
	void ColorPipeline::setColor(const Vector4& color)
	{
		throw std::runtime_error("Not implemented color pipeline function");
	}
}
