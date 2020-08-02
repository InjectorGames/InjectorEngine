#include <injector/graphics/gl_batch.hpp>

#include <GL/glew.h>
#include <SDL_opengl.h>

namespace INJECTOR_NAMESPACE
{
	uint32_t GlBatch::create() noexcept
	{
		GLuint vertexArray;
		glGenVertexArrays(GL_ONE, &vertexArray);
		return static_cast<uint32_t>(vertexArray);
	}
	void GlBatch::destroy(uint32_t vertexArray) noexcept
	{
		glDeleteVertexArrays(GL_ONE, static_cast<const GLuint*>(&vertexArray));
	}
	void GlBatch::bind(uint32_t vertexArray) noexcept
	{
		glBindVertexArray(static_cast<GLuint>(vertexArray));
	}

	GlBatch::GlBatch()
	{
		instance = create();
	}
	GlBatch::~GlBatch()
	{
		destroy(instance);
	}

	uint32_t GlBatch::getInstance() const noexcept
	{
		return instance;
	}

	void GlBatch::bind() noexcept
	{
		bind(instance);
	}
	void GlBatch::unbind() noexcept
	{
		bind(GL_ZERO);
	}
}
