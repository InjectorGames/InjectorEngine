#include <injector/graphics/diffuse_pipeline.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	DiffusePipeline::~DiffusePipeline()
	{}

	const Vector4& DiffusePipeline::getObjectColor() const
	{
		throw std::runtime_error("Not implemented diffuse pipeline function");
	}
	void DiffusePipeline::setObjectColor(const Vector4& color)
	{
		throw std::runtime_error("Not implemented diffuse pipeline function");
	}

	const Vector4& DiffusePipeline::getAmbientColor() const
	{
		throw std::runtime_error("Not implemented diffuse pipeline function");
	}
	void DiffusePipeline::setAmbientColor(const Vector4& color)
	{
		throw std::runtime_error("Not implemented diffuse pipeline function");
	}

	const Vector4& DiffusePipeline::getLightColor() const
	{
		throw std::runtime_error("Not implemented diffuse pipeline function");
	}
	void DiffusePipeline::setLightColor(const Vector4& color)
	{
		throw std::runtime_error("Not implemented diffuse pipeline function");
	}

	const Vector3& DiffusePipeline::getLightDirection() const
	{
		throw std::runtime_error("Not implemented diffuse pipeline function");
	}
	void DiffusePipeline::setLightDirection(const Vector3& lightDirection)
	{
		throw std::runtime_error("Not implemented diffuse pipeline function");
	}
}