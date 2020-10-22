#pragma once
#include "Injector/Graphics/GpuBuffer.hpp"

#include <vector>
#include <memory>
#include <cstdlib>

namespace Injector
{
	class GpuMesh
	{
	 public:
		size_t indexCount;

		explicit GpuMesh(size_t indexCount);
		GpuMesh(GpuMesh&& mesh) = delete;
		GpuMesh(const GpuMesh& mesh) = delete;
		virtual ~GpuMesh() = default;

		virtual std::shared_ptr<GpuBuffer> getVertexBuffer() const = 0;
		virtual void setVertexBuffer(const std::shared_ptr<GpuBuffer>& buffer) = 0;

		virtual std::shared_ptr<GpuBuffer> getIndexBuffer() const = 0;
		virtual void setIndexBuffer(const std::shared_ptr<GpuBuffer>& buffer) = 0;
	};
}
