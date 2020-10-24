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
				std::string(typeid(GlGpuMesh).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Buffer type is not vertex");
		}
		if(_indexBuffer && _indexBuffer->getType() != GpuBufferType::Index)
		{
			throw Exception(
				std::string(typeid(GlGpuMesh).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Buffer type is not index");
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
				std::string(typeid(GlGpuMesh).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Buffer type is not vertex");
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
				std::string(typeid(GlGpuMesh).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Buffer type is not index");
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
				std::string(typeid(GlGpuMesh).name()),
				std::string(__func__),
				std::to_string(__LINE__),
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
