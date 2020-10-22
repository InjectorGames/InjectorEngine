#include "Injector/Graphics/GpuPipeline.hpp"

namespace Injector
{
	GpuPipeline::GpuPipeline(
		PrimitiveTopology _primitiveTopology) :
		primitiveTopology(_primitiveTopology)
	{
	}

	PrimitiveTopology GpuPipeline::getPrimitiveTopology() const noexcept
	{
		return primitiveTopology;
	}
}
