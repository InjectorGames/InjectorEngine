#include "Injector/Graphics/GlMesh.hpp"
#include <stdexcept>

namespace Injector
{
	GlMesh::GlMesh(
		size_t indexCount,
		BufferIndex indexType,
		const std::shared_ptr<GlBuffer>& _vertexBuffer,
		const std::shared_ptr<GlBuffer>& _indexBuffer) :
		Mesh(indexCount, indexType),
		vertexBuffer(_vertexBuffer),
		indexBuffer(_indexBuffer)
	{
		glGenVertexArrays(GL_ONE, &vertexArray);

		glBindVertexArray(vertexArray);
		_vertexBuffer->bind();
		_indexBuffer->bind();

		glBindVertexArray(GL_ZERO);
		_vertexBuffer->unbind();
		_indexBuffer->unbind();
	}
	GlMesh::~GlMesh()
	{
		glDeleteVertexArrays(GL_ONE, &vertexArray);
	}

	GLuint GlMesh::getVertexArray() const noexcept
	{
		return vertexArray;
	}
	const std::shared_ptr<GlBuffer>& GlMesh::getVertexBuffer() const noexcept
	{
		return vertexBuffer;
	}
	const std::shared_ptr<GlBuffer>& GlMesh::getIndexBuffer() const noexcept
	{
		return indexBuffer;
	}

	void GlMesh::draw(GLuint mode, 
		const std::vector<GlVertexAttribute>& vertexAttributes) noexcept
	{
		glBindVertexArray(vertexArray);
		vertexBuffer->bind();
		indexBuffer->bind();

		for (auto& vertexAttribute : vertexAttributes)
		{
			vertexAttribute.enable();
			vertexAttribute.setPointer();
		}
		
		auto index = (indexType == BufferIndex::UnsignedShort) ?
			GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;

		glDrawElements(mode, static_cast<GLsizei>(indexCount), index, nullptr);

		glBindVertexArray(GL_ZERO);
		vertexBuffer->unbind();
		indexBuffer->unbind();
	}

	void GlMesh::setVertexData(void* data, size_t size)
	{
		vertexBuffer->setData(data, size);
	}
	void GlMesh::setVertexData(void* data, size_t size, size_t offset)
	{
		vertexBuffer->setData(data, size, offset);
	}

	void GlMesh::setIndexData(void* data, size_t size)
	{
		indexBuffer->setData(data, size);
	}
	void GlMesh::setIndexData(void* data, size_t size, size_t offset)
	{
		indexBuffer->setData(data, size, offset);
	}
}
