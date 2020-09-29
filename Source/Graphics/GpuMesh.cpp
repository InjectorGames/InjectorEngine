#include "Injector/Graphics/GpuMesh.hpp"

namespace Injector
{
	GpuMesh::GpuMesh(
		size_t _indexCount,
		GpuBufferIndex _indexType,
		const std::shared_ptr<GpuBuffer>& _vertexBuffer,
		const std::shared_ptr<GpuBuffer>& _indexBuffer) :
		indexCount(_indexCount),
		indexType(_indexType),
		vertexBuffer(_vertexBuffer),
		indexBuffer(_indexBuffer)
	{
	}
}
