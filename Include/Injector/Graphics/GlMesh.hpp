#pragma once
#include "Injector/Graphics/Mesh.hpp"
#include "Injector/Graphics/GlBuffer.hpp"
#include "Injector/Graphics/GlVertexAttribute.hpp"

#include <vector>
#include <memory>

namespace Injector
{
	class GlMesh : public Mesh
	{
	protected:
		GLuint vertexArray;
		std::shared_ptr<GlBuffer> vertexBuffer;
		std::shared_ptr<GlBuffer> indexBuffer;
	public:
		GlMesh(size_t indexCount,
			BufferIndex indexType,
			const std::shared_ptr<GlBuffer>& vertexBuffer,
			const std::shared_ptr<GlBuffer>& indexBuffer);
		virtual ~GlMesh();

		GLuint getVertexArray() const noexcept;
		const std::shared_ptr<GlBuffer>& getVertexBuffer() const noexcept;
		const std::shared_ptr<GlBuffer>& getIndexBuffer() const noexcept;

		void draw(GLuint mode,
			const std::vector<GlVertexAttribute>& vertexAttributes) noexcept;

		void setVertexData(void* data, size_t size) override;
		void setVertexData(void* data, size_t size, size_t offset) override;

		void setIndexData(void* data, size_t size) override;
		void setIndexData(void* data, size_t size, size_t offset) override;
	};
}
