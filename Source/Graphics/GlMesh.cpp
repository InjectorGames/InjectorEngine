#include "Injector/Graphics/GlMesh.hpp"
#include "Injector/Graphics/GraphicsException.hpp"

namespace Injector
{
	GlMesh::GlMesh(
		size_t indexCount,
		BufferIndex indexType,
		const std::shared_ptr<Buffer>& vertexBuffer,
		const std::shared_ptr<Buffer>& indexBuffer) :
		Mesh(indexCount, indexType, vertexBuffer, indexBuffer)
	{
		if(!std::dynamic_pointer_cast<GlBuffer>(vertexBuffer) ||
			!std::dynamic_pointer_cast<GlBuffer>(indexBuffer))
		{
			throw GraphicsException("Failed to cast OpenGL buffer");
		}	

		glGenVertexArrays(GL_ONE, &vertexArray);
	}
	GlMesh::~GlMesh()
	{
		glDeleteVertexArrays(GL_ONE, &vertexArray);
	}

	GLuint GlMesh::getVertexArray() const noexcept
	{
		return vertexArray;
	}

	void GlMesh::draw(GLuint mode, 
		const std::vector<GlVertexAttribute>& vertexAttributes) noexcept
	{
		auto glVertexBuffer = std::dynamic_pointer_cast<GlBuffer>(vertexBuffer);
		auto glIndexBuffer = std::dynamic_pointer_cast<GlBuffer>(indexBuffer);

		glBindVertexArray(vertexArray);
		glVertexBuffer->bind();
		glIndexBuffer->bind();

		for (auto& vertexAttribute : vertexAttributes)
		{
			vertexAttribute.enable();
			vertexAttribute.setPointer();
		}
		
		auto index = (indexType == BufferIndex::UnsignedShort) ?
			GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;

		glDrawElements(mode, static_cast<GLsizei>(indexCount), index, nullptr);

		glBindVertexArray(GL_ZERO);
		glVertexBuffer->unbind();
		glIndexBuffer->unbind();
	}

	void GlMesh::setVertexBuffer(const std::shared_ptr<Buffer>& _vertexBuffer)
	{
		if(!std::dynamic_pointer_cast<GlBuffer>(_vertexBuffer))
			throw GraphicsException("Failed to cast OpenGL vertex buffer");

		vertexBuffer = std::shared_ptr<Buffer>(_vertexBuffer);
	}
	void GlMesh::setIndexBuffer(const std::shared_ptr<Buffer>& _indexBuffer)
	{
		if(!std::dynamic_pointer_cast<GlBuffer>(_indexBuffer))
			throw GraphicsException("Failed to cast OpenGL index buffer");

		indexBuffer = std::shared_ptr<Buffer>(_indexBuffer);
	}
}
