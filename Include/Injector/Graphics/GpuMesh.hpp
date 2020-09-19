#pragma once
#include "Injector/Graphics/GpuBuffer.hpp"
#include "Injector/Graphics/GpuBufferIndex.hpp"

#include <vector>
#include <cstdlib>

namespace Injector
{
	class GpuMesh
	{
	 public:
		size_t indexCount;
		GpuBufferIndex indexType;
		std::shared_ptr<GpuBuffer> vertexBuffer;
		std::shared_ptr<GpuBuffer> indexBuffer;

		GpuMesh(
			size_t indexCount,
			GpuBufferIndex indexType,
			const std::shared_ptr<GpuBuffer>& vertexBuffer,
			const std::shared_ptr<GpuBuffer>& indexBuffer);
		virtual ~GpuMesh();
	};
}
