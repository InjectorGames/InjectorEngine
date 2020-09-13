#pragma once
#include "Injector/Graphics/Mesh.hpp"
#include "Injector/Graphics/GlBuffer.hpp"
#include "Injector/Graphics/GlPipeline.hpp"

#include <vector>
#include <memory>

namespace Injector
{
	class GlMesh : public Mesh
	{
	protected:
		GLuint vertexArray;
	public:
		GlMesh(size_t indexCount,
			BufferIndex indexType,
			const std::shared_ptr<Buffer>& vertexBuffer,
			const std::shared_ptr<Buffer>& indexBuffer);
		virtual ~GlMesh();

		GLuint getVertexArray() const noexcept;

		void draw(const std::shared_ptr<GlPipeline>& pipeline) noexcept;

		void setVertexBuffer(const std::shared_ptr<Buffer>& vertexBuffer) override;
		void setIndexBuffer(const std::shared_ptr<Buffer>& indexBuffer) override;
	};
}
