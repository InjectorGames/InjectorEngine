#pragma once
#include <injector/defines.hpp>
#include <GL/glew.h>

#include <cstdint>

namespace INJECTOR_NAMESPACE
{
	struct GlVertexAttribute
	{
		/*enum class Type : GLenum
		{
			Byte = GL_BYTE,
			UnsignedByte = GL_UNSIGNED_BYTE,
			Short = GL_SHORT,
			UnsignedShort = GL_UNSIGNED_SHORT,
			Int = GL_INT,
			UnsignedInt = GL_UNSIGNED_INT,
			HalfFloat = GL_HALF_FLOAT,
			Float = GL_FLOAT,
			Double = GL_DOUBLE,
			Fixed = GL_FIXED,
			Int_2_10_10_10_Rev = GL_INT_2_10_10_10_REV,
			UnsignedInt_2_10_10_10_Rev = GL_UNSIGNED_INT_2_10_10_10_REV,
			UnsignedInt_10f_11f_11f_Rev = GL_UNSIGNED_INT_10F_11F_11F_REV, // GL 4.4
		};*/

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
