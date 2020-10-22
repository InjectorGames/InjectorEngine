#include "Injector/Graphics/OpenGL/GlGpuMesh.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	GlGpuMesh::GlGpuMesh(
		size_t indexCount,
		const std::shared_ptr<GlGpuBuffer>& _vertexBuffer,
		const std::shared_ptr<GlGpuBuffer>& _indexBuffer) :
		GpuMesh(indexCount),
		vertexBuffer(_vertexBuffer),
		indexBuffer(_indexBuffer)
	{
		if(_vertexBuffer && _vertexBuffer->getType() != GpuBufferType::Vertex)
		{
			throw Exception(
				"GlGpuMesh",
				"GlGpuMesh",
				"Buffer has not vertex type");
		}
		if(_indexBuffer && _indexBuffer->getType() != GpuBufferType::Index)
		{
			throw Exception(
				"GlGpuMesh",
				"GlGpuMesh",
				"Buffer has not index type");
		}

		glGenVertexArrays(GL_ONE, &vertexArray);
	}
	GlGpuMesh::~GlGpuMesh()
	{
		glDeleteVertexArrays(GL_ONE, &vertexArray);
	}

	std::shared_ptr<GpuBuffer> GlGpuMesh::getVertexBuffer() const
	{
		return vertexBuffer;
	}
	void GlGpuMesh::setVertexBuffer(const std::shared_ptr<GpuBuffer>& buffer)
	{
		if(buffer && buffer->getType() != GpuBufferType::Vertex)
		{
			throw Exception(
				"GlGpuMesh",
				"setVertexBuffer",
				"Buffer has not vertex type");
		}

		vertexBuffer = std::dynamic_pointer_cast<GlGpuBuffer>(buffer);
	}

	std::shared_ptr<GpuBuffer> GlGpuMesh::getIndexBuffer() const
	{
		return indexBuffer;
	}
	void GlGpuMesh::setIndexBuffer(const std::shared_ptr<GpuBuffer>& buffer)
	{
		if(buffer && buffer->getType() != GpuBufferType::Index)
		{
			throw Exception(
				"GlGpuMesh",
				"setIndexBuffer",
				"Buffer has not index type");
		}

		indexBuffer = std::dynamic_pointer_cast<GlGpuBuffer>(buffer);
	}

	GLuint GlGpuMesh::getVertexArray() const noexcept
	{
		return vertexArray;
	}

	void GlGpuMesh::draw(const std::shared_ptr<GlGpuPipeline>& pipeline)
	{
		if(!pipeline)
		{
			throw NullException(
				"GlGpuMesh",
				"draw",
				"pipeline");
		}

		if (!vertexBuffer || !indexBuffer)
			return;

		glBindVertexArray(vertexArray);
		vertexBuffer->bind();
		indexBuffer->bind();
		pipeline->setAttributes();

		glDrawElements(
			pipeline->getGlDrawMode(),
			static_cast<GLsizei>(indexCount),
			GL_UNSIGNED_INT,
			nullptr);

		glBindVertexArray(GL_ZERO);
		vertexBuffer->unbind();
		indexBuffer->unbind();
	}
}
