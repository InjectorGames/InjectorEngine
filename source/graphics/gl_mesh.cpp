#include <injector/graphics/gl_mesh.hpp>

#include <GL/glew.h>
#include <SDL_opengl.h>

namespace INJECTOR_NAMESPACE
{
	void GlMesh::draw(const uint32_t mode, 
		const uint32_t type, const size_t count) noexcept
	{
		glDrawElements(static_cast<GLenum>(mode),
			static_cast<GLsizei>(count), static_cast<GLenum>(type), nullptr);
	}

	GlMesh::GlMesh(const GlBufferHandle& _vertexBuffer,
		const GlBufferHandle& _indexBuffer,
		const std::vector<GlAttribute>& _attributes,
		uint32_t _drawMode,
		uint32_t _drawType,
		uint32_t _indexCount) :
		batch(),
		vertexBuffer(_vertexBuffer),
		indexBuffer(_indexBuffer),
		drawMode(_drawMode),
		drawType(_drawType),
		indexCount(_indexCount)
	{
		batch.bind();
		vertexBuffer->bind();
		indexBuffer->bind();

		for (auto& attribute : _attributes)
		{
			attribute.enable();
			attribute.setPointer();
		}

		batch.unbind();
		vertexBuffer->unbind();
		indexBuffer->unbind();
	}
	GlMesh::~GlMesh()
	{}

	void GlMesh::draw()
	{
		batch.bind();
		draw(drawMode, drawType, indexCount);
		batch.unbind();
	}

	const GlBatch& GlMesh::getBatch() const noexcept
	{
		return batch;
	}
	const GlBufferHandle& GlMesh::getVertexBuffer() const noexcept
	{
		return vertexBuffer;
	}
	const GlBufferHandle& GlMesh::getIndexBuffer() const noexcept
	{
		return indexBuffer;
	}
}
