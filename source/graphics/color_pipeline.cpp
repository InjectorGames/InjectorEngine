#include <injector/graphics/color_pipeline.hpp>

namespace INJECTOR_NAMESPACE
{
	ColorPipeline::ColorPipeline(
		const Matrix4& _mvp,
		const Vector4& _color) :
		mvp(_mvp),
		color(_color)
	{}
	ColorPipeline::~ColorPipeline()
	{}

	const Matrix4& ColorPipeline::getMVP() const noexcept
	{
		return mvp;
	}
	const Vector4& ColorPipeline::getColor() const noexcept
	{
		return color;
	}

	void ColorPipeline::setMVP(const Matrix4& _mvp) noexcept
	{
		mvp = Matrix4(_mvp);
	}
	void ColorPipeline::setColor(const Vector4& _color) noexcept
	{
		color = Vector4(_color);
	}
}
