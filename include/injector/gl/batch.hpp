#pragma once
#include <inject/defines.hpp>

#include <GL/glew.h>
#include <SDL_opengl.h>

namespace INJECT_NAMESPACE
{
	class GlBatch
	{
	protected:
		uint32_t vertexArray;

		inline static const uint32_t create() noexcept
		{
			GLuint vertexArray;
			glGenVertexArrays(GL_ONE, &vertexArray);
			return static_cast<uint32_t>(vertexArray);
		}
		inline static void destroy(const uint32_t vertexArray) noexcept
		{
			glDeleteVertexArrays(GL_ONE, static_cast<const GLuint*>(&vertexArray));
		}

		inline static void bind(const uint32_t vertexArray) noexcept
		{
			glBindVertexArray(static_cast<GLuint>(vertexArray));
		}
	public:
		GlBatch()
		{
			vertexArray = create();
		}
		virtual ~GlBatch()
		{
			destroy(vertexArray);
		}

		inline const uint32_t getVertexArray() const noexcept
		{
			return vertexArray;
		}

		inline void bind() const noexcept
		{
			bind(vertexArray);
		}
		inline static void unbind() noexcept
		{
			bind(0);
		}
	};
}
