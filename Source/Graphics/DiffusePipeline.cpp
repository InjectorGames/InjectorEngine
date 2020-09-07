#include "Injector/Graphics/DiffusePipeline.hpp"
#include "Injector/Graphics/GraphicsException.hpp"

namespace Injector
{
	DiffusePipeline::~DiffusePipeline()
	{}

	const Vector4& DiffusePipeline::getObjectColor() const
	{
		throw GraphicsException("Not implemented diffuse pipeline function");
	}
	void DiffusePipeline::setObjectColor(const Vector4& color)
	{
		throw GraphicsException("Not implemented diffuse pipeline function");
	}

	const Vector4& DiffusePipeline::getAmbientColor() const
	{
		throw GraphicsException("Not implemented diffuse pipeline function");
	}
	void DiffusePipeline::setAmbientColor(const Vector4& color)
	{
		throw GraphicsException("Not implemented diffuse pipeline function");
	}

	const Vector4& DiffusePipeline::getLightColor() const
	{
		throw GraphicsException("Not implemented diffuse pipeline function");
	}
	void DiffusePipeline::setLightColor(const Vector4& color)
	{
		throw GraphicsException("Not implemented diffuse pipeline function");
	}

	const Vector3& DiffusePipeline::getLightDirection() const
	{
		throw GraphicsException("Not implemented diffuse pipeline function");
	}
	void DiffusePipeline::setLightDirection(const Vector3& lightDirection)
	{
		throw GraphicsException("Not implemented diffuse pipeline function");
	}
}