#include "Injector/Graphics/Pipeline/SimSkyGpuPipeline.hpp"
#include "Injector/Exception/NotImplementedException.hpp"

namespace Injector
{
	SimSkyGpuPipeline::~SimSkyGpuPipeline()
	{
	}

	float SimSkyGpuPipeline::getHeight() const
	{
		throw NotImplementedException(
			"SimSkyGpuPipeline",
			"getHeight");
	}
	void SimSkyGpuPipeline::setHeight(float height)
	{
		throw NotImplementedException(
			"SimSkyGpuPipeline",
			"setHeight");
	}
}
