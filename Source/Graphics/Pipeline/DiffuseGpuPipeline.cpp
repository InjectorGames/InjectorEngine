#include "Injector/Graphics/Pipeline/DiffuseGpuPipeline.hpp"
#include "Injector/Exception/NotImplementedException.hpp"

namespace Injector
{
	DiffuseGpuPipeline::~DiffuseGpuPipeline()
	{}

	const Vector4& DiffuseGpuPipeline::getObjectColor() const
	{
		throw NotImplementedException("DiffuseGpuPipeline", "getObjectColor");
	}
	void DiffuseGpuPipeline::setObjectColor(const Vector4& color)
	{
		throw NotImplementedException("DiffuseGpuPipeline", "setObjectColor");
	}

	const Vector4& DiffuseGpuPipeline::getAmbientColor() const
	{
		throw NotImplementedException("DiffuseGpuPipeline", "getAmbientColor");
	}
	void DiffuseGpuPipeline::setAmbientColor(const Vector4& color)
	{
		throw NotImplementedException("DiffuseGpuPipeline", "setAmbientColor");
	}

	const Vector4& DiffuseGpuPipeline::getLightColor() const
	{
		throw NotImplementedException("DiffuseGpuPipeline", "getLightColor");
	}
	void DiffuseGpuPipeline::setLightColor(const Vector4& color)
	{
		throw NotImplementedException("DiffuseGpuPipeline", "setLightColor");
	}

	const Vector3& DiffuseGpuPipeline::getLightDirection() const
	{
		throw NotImplementedException("DiffuseGpuPipeline", "getLightDirection");
	}
	void DiffuseGpuPipeline::setLightDirection(const Vector3& direction)
	{
		throw NotImplementedException("DiffuseGpuPipeline", "setLightDirection");
	}
}