#include "Injector/Graphics/DiffusePipeline.hpp"
#include "Injector/Exception/NotImplementedException.hpp"

namespace Injector
{
	DiffusePipeline::~DiffusePipeline()
	{}

	const Vector4& DiffusePipeline::getObjectColor() const
	{
		throw NotImplementedException("DiffusePipeline", "getObjectColor");
	}
	void DiffusePipeline::setObjectColor(const Vector4& color)
	{
		throw NotImplementedException("DiffusePipeline", "setObjectColor");
	}

	const Vector4& DiffusePipeline::getAmbientColor() const
	{
		throw NotImplementedException("DiffusePipeline", "getAmbientColor");
	}
	void DiffusePipeline::setAmbientColor(const Vector4& color)
	{
		throw NotImplementedException("DiffusePipeline", "setAmbientColor");
	}

	const Vector4& DiffusePipeline::getLightColor() const
	{
		throw NotImplementedException("DiffusePipeline", "getLightColor");
	}
	void DiffusePipeline::setLightColor(const Vector4& color)
	{
		throw NotImplementedException("DiffusePipeline", "setLightColor");
	}

	const Vector3& DiffusePipeline::getLightDirection() const
	{
		throw NotImplementedException("DiffusePipeline", "getLightDirection");
	}
	void DiffusePipeline::setLightDirection(const Vector3& direction)
	{
		throw NotImplementedException("DiffusePipeline", "setLightDirection");
	}
}