#include "Injector/Graphics/Pipeline/SimulatedSkyGpuPipeline.hpp"
#include "Injector/Exception/NotImplementedException.hpp"

namespace Injector
{
	SimulatedSkyGpuPipeline::~SimulatedSkyGpuPipeline()
	{
	}

	float SimulatedSkyGpuPipeline::getHeight() const
	{
		throw NotImplementedException(
			"SimulatedSkyGpuPipeline",
			"getHeight");
	}
	void SimulatedSkyGpuPipeline::setHeight(float height)
	{
		throw NotImplementedException(
			"SimulatedSkyGpuPipeline",
			"setHeight");
	}
}
