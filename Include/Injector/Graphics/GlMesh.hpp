#pragma once
#include "Injector/Graphics/Mesh.hpp"
#include "Injector/Graphics/GlBuffer.hpp"
#include "Injector/Graphics/GlVertexAttribute.hpp"

#include <vector>

namespace Injector::Graphics
{
	using namespace std;

	class GlMesh : public Mesh
	{
	protected:
		GLuint vertexArray;
		shared_ptr<GlBuffer> vertexBuffer;
		shared_ptr<GlBuffer> indexBuffer;
	public:
		GlMesh(size_t indexCount,
			BufferIndex indexType,
			const shared_ptr<GlBuffer>& vertexBuffer,
			const shared_ptr<GlBuffer>& indexBuffer);
		virtual ~GlMesh();

		GLuint getVertexArray() const noexcept;
		const shared_ptr<GlBuffer>& getVertexBuffer() const noexcept;
		const shared_ptr<GlBuffer>& getIndexBuffer() const noexcept;

		void draw(GLuint mode,
			const vector<GlVertexAttribute>& vertexAttributes) noexcept;

		void setVertexData(void* data, size_t size) override;
		void setVertexData(void* data, size_t size, size_t offset) override;

		void setIndexData(void* data, size_t size) override;
		void setIndexData(void* data, size_t size, size_t offset) override;
	};
}
