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

		std::shared_ptr<GlGpuBuffer> vertexBuffer;
		std::shared_ptr<GlGpuBuffer> indexBuffer;
	 public:
		GlGpuMesh(
			size_t indexCount,
			const std::shared_ptr<GlGpuBuffer>& vertexBuffer,
			const std::shared_ptr<GlGpuBuffer>& indexBuffer);
		virtual ~GlGpuMesh();

		std::shared_ptr<GpuBuffer> getVertexBuffer() const override;
		void setVertexBuffer(const std::shared_ptr<GpuBuffer>& buffer) override;

		std::shared_ptr<GpuBuffer> getIndexBuffer() const override;
		void setIndexBuffer(const std::shared_ptr<GpuBuffer>& buffer) override;

		GLuint getVertexArray() const noexcept;

		void draw(const std::shared_ptr<GlGpuPipeline>& pipeline);
	};
}
