#include <injector/graphics/gl_mesh.hpp>

#include <GL/glew.h>
#include <SDL_opengl.h>

#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	GlMesh::GlMesh(
		size_t indexCount,
		MeshIndex indexType,
		const BufferHandle& vertexBuffer,
		const BufferHandle& indexBuffer,
		const std::vector<GlAttribute>& attributes) :
		Mesh(indexCount, indexType, vertexBuffer, indexBuffer)
	{
		glIndexType = toGlIndexType(indexType);

		glGenVertexArrays(GL_ONE, &vertexArray);

		glBindVertexArray(vertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, 
			std::dynamic_pointer_cast<GlBuffer>(vertexBuffer)->getBuffer());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 
			std::dynamic_pointer_cast<GlBuffer>(indexBuffer)->getBuffer());

		for (auto& attribute : attributes)
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

	GLuint GlMesh::getVertexArray() const noexcept
	{
		return vertexArray;
	}
	GLenum GlMesh::getGlIndexType() const noexcept
	{
		return glIndexType;
	}

	void GlMesh::draw(GLuint mode) noexcept
	{
		glBindVertexArray(vertexArray);
		glDrawElements(mode, static_cast<GLsizei>(indexCount), glIndexType, nullptr);
		glBindVertexArray(GL_ZERO);
	}

	GLenum GlMesh::toGlIndexType(MeshIndex indexType)
	{
		if (indexType == MeshIndex::Ushort)
			return GL_UNSIGNED_SHORT;
		else if (indexType == MeshIndex::Uint)
			return GL_UNSIGNED_INT;
		else
			throw std::runtime_error("Unsupported OpenGL mesh index type");
	}
	MeshIndex GlMesh::toIndexType(GLenum indexType)
	{
		if (indexType == GL_UNSIGNED_SHORT)
			return MeshIndex::Ushort;
		else if (indexType == GL_UNSIGNED_INT)
			return MeshIndex::Uint;
		else
			throw std::runtime_error("Unsupported OpenGL mesh index type");
	}
}
