#include <injector/graphics/gl_mesh.hpp>

#include <GL/glew.h>
#include <SDL_opengl.h>

#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	GlMesh::GlMesh(GLenum _index,
		const GlBufferHandle& _vertexBuffer,
		const GlBufferHandle& _indexBuffer,
		const std::vector<GlAttribute>& _attributes,
		uint32_t _drawType,
		uint32_t _indexCount) :
		index(_index),
		vertexBuffer(_vertexBuffer),
		indexBuffer(_indexBuffer),
		drawType(_drawType),
		indexCount(_indexCount)
	{
		glGenVertexArrays(GL_ONE, &vertexArray);

		glBindVertexArray(vertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getBuffer());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->getBuffer());

		for (auto& attribute : _attributes)
		{
			attribute.enable();
			attribute.setPointer();
		}

		glBindVertexArray(GL_ZERO);
		glBindBuffer(GL_ARRAY_BUFFER, GL_ZERO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_ZERO);
	}
	GlMesh::~GlMesh()
	{
		glDeleteVertexArrays(GL_ONE, &vertexArray);
	}

	/*void GlMesh::draw(size_t frameIndex)
	{
		glBindVertexArray(static_cast<GLuint>(vertexArray));

		glDrawElements(static_cast<GLenum>(drawMode), static_cast<GLsizei>(indexCount),
			static_cast<GLenum>(drawType), nullptr);

		glBindVertexArray(GL_ZERO);
	}*/

	uint32_t GlMesh::getVertexArray() const noexcept
	{
		return vertexArray;
	}

	MeshIndex GlMesh::getIndex() const
	{
		return toIndex(index);
	}
	void GlMesh::setIndex(MeshIndex _index)
	{
		index = toGlIndex(_index);
	}

	const BufferHandle& GlMesh::getVertexBuffer() const
	{
		return vertexBuffer;
	}
	const BufferHandle& GlMesh::getIndexBuffer() const
	{
		return indexBuffer;
	}

	GLenum GlMesh::toGlIndex(MeshIndex index)
	{
		if (index == MeshIndex::Ushort)
			return GL_UNSIGNED_SHORT;
		else if (index == MeshIndex::Uint)
			return GL_UNSIGNED_INT;
		else
			throw std::runtime_error("Unsupported Vulkan mesh index type");
	}
	MeshIndex GlMesh::toIndex(GLenum index)
	{
		if (index == GL_UNSIGNED_SHORT)
			return MeshIndex::Ushort;
		else if (index == GL_UNSIGNED_INT)
			return MeshIndex::Uint;
		else
			throw std::runtime_error("Unsupported Vulkan mesh index type");
	}
}
