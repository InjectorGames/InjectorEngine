#include "Injector/Graphics/Pipeline/SkyGpuPipeline.hpp"
#include "Injector/Exception/NotImplementedException.hpp"

namespace Injector
{
    SkyGpuPipeline::~SkyGpuPipeline()
    {}

	float SkyGpuPipeline::getHeight() const
    {
        throw NotImplementedException("SkyGpuPipeline", "getheight");
    }
	void SkyGpuPipeline::setHeight(float height)
    {
        throw NotImplementedException("SkyGpuPipeline", "setheight");
    }
}
