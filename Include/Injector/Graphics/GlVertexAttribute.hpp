#pragma once
#include "GL/glew.h"
#include <cstdint>

namespace Injector
{
	struct GlVertexAttribute
	{
		GLuint index;
		GLint size;
		GLenum type;
		bool normalized;
		size_t stride;
		size_t offset;

		GlVertexAttribute(
			const GLuint index,
			const GLint size,
			const GLenum type,
			const bool normalized,
			const size_t stride,
			const size_t offset);

		void enable() const noexcept;
		void disable() const noexcept;
		void setPointer() const noexcept;
	};
}
