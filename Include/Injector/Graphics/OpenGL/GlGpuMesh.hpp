#pragma once
#include "Injector/Graphics/GpuMesh.hpp"
#include "Injector/Graphics/OpenGL/GlGpuBuffer.hpp"
#include "Injector/Graphics/OpenGL/GlGpuPipeline.hpp"

#include <vector>
#include <memory>

namespace Injector
{
	class GlGpuMesh : public GpuMesh
	{
	 protected:
		GLuint vertexArray;
	 public:
		GlGpuMesh(
			size_t indexCount,
			GpuBufferIndex indexType,
			const std::shared_ptr<GpuBuffer>& vertexBuffer,
			const std::shared_ptr<GpuBuffer>& indexBuffer);
		virtual ~GlGpuMesh();

		GLuint getVertexArray() const noexcept;

		void draw(const std::shared_ptr<GlGpuPipeline>& pipeline);
	};
}
