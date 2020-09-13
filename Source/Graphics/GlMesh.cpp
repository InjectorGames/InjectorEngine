#include "Injector/Graphics/GlMesh.hpp"
#include "Injector/Exception/CastException.hpp"

namespace Injector
{
	GlMesh::GlMesh(
		size_t indexCount,
		BufferIndex indexType,
		const std::shared_ptr<Buffer>& vertexBuffer,
		const std::shared_ptr<Buffer>& indexBuffer) :
		Mesh(indexCount, indexType, vertexBuffer, indexBuffer)
	{
		if(!std::dynamic_pointer_cast<GlBuffer>(vertexBuffer))
			throw CastException("GlMesh", "GlMesh", "vertexBuffer");
		if(!std::dynamic_pointer_cast<GlBuffer>(indexBuffer))
			throw CastException("GlMesh", "GlMesh", "indexBuffer");

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

	void GlMesh::draw(const std::shared_ptr<GlPipeline>& pipeline) noexcept
	{
		auto glVertexBuffer = std::dynamic_pointer_cast<GlBuffer>(vertexBuffer);
		auto glIndexBuffer = std::dynamic_pointer_cast<GlBuffer>(indexBuffer);

		glBindVertexArray(vertexArray);
		glVertexBuffer->bind();
		glIndexBuffer->bind();
		pipeline->setAttributes();
		
		auto index = (indexType == BufferIndex::UnsignedShort) ?
			GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;

		glDrawElements(pipeline->getDrawMode(),
			static_cast<GLsizei>(indexCount), index, nullptr);

		glBindVertexArray(GL_ZERO);
		glVertexBuffer->unbind();
		glIndexBuffer->unbind();
	}

	void GlMesh::setVertexBuffer(const std::shared_ptr<Buffer>& _vertexBuffer)
	{
		if(!std::dynamic_pointer_cast<GlBuffer>(_vertexBuffer))
			throw CastException("GlMesh", "setVertexBuffer", "vertexBuffer");

		vertexBuffer = std::shared_ptr<Buffer>(_vertexBuffer);
	}
	void GlMesh::setIndexBuffer(const std::shared_ptr<Buffer>& _indexBuffer)
	{
		if(!std::dynamic_pointer_cast<GlBuffer>(_indexBuffer))
			throw CastException("GlMesh", "setIndexBuffer", "indexBuffer");

		indexBuffer = std::shared_ptr<Buffer>(_indexBuffer);
	}
}
