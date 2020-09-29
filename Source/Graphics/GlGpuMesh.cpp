#include "Injector/Graphics/GlGpuMesh.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	GlGpuMesh::GlGpuMesh(
		size_t indexCount,
		GpuBufferIndex indexType,
		const std::shared_ptr<GpuBuffer>& vertexBuffer,
		const std::shared_ptr<GpuBuffer>& indexBuffer) :
		GpuMesh(
			indexCount,
			indexType,
			vertexBuffer,
			indexBuffer)
	{
		glGenVertexArrays(GL_ONE, &vertexArray);
	}
	GlGpuMesh::~GlGpuMesh()
	{
		glDeleteVertexArrays(GL_ONE, &vertexArray);
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

		auto glVertexBuffer = std::dynamic_pointer_cast<GlGpuBuffer>(vertexBuffer);
		auto glIndexBuffer = std::dynamic_pointer_cast<GlGpuBuffer>(indexBuffer);

		if (!glVertexBuffer || !glIndexBuffer)
			return;

		glBindVertexArray(vertexArray);
		glVertexBuffer->bind();
		glIndexBuffer->bind();
		pipeline->setAttributes();

		auto index = (indexType == GpuBufferIndex::UnsignedShort) ?
			GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;

		glDrawElements(
			pipeline->getDrawMode(),
			static_cast<GLsizei>(indexCount),
			index,
			nullptr);

		glBindVertexArray(GL_ZERO);
		glVertexBuffer->unbind();
		glIndexBuffer->unbind();
	}
}
