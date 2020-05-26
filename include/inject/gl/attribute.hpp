#pragma once
#include <GL/glew.h>
#include <SDL_opengl.h>

namespace inject
{
	struct GlAttribute
	{
		enum class Type : GLenum
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
		};
		enum class Size
		{
			One = 1,
			Two = 2,
			Three = 3,
			Four = 4,
		};

		uint32_t index;
		Size size;
		Type type;
		bool normalized;
		int32_t stride;
		uint64_t offset;

		GlAttribute(const uint32_t _index,
			const Size _size,
			const Type _type,
			const bool _normalized,
			const int32_t _stride,
			const uint64_t _offset) :
			index(_index),
			size(_size),
			type(_type),
			normalized(_normalized),
			stride(_stride),
			offset(_offset)
		{}

		inline void enable() const noexcept
		{
			glEnableVertexAttribArray(static_cast<GLuint>(index));
		}
		inline void disable() const noexcept
		{
			glDisableVertexAttribArray(static_cast<GLuint>(index));
		}

		inline void setPointer() const noexcept
		{
			glVertexAttribPointer(
				static_cast<GLuint>(index),
				static_cast<GLint>(size),
				static_cast<GLenum>(type),
				normalized ? GL_TRUE : GL_FALSE,
				static_cast<GLsizei>(stride),
				reinterpret_cast<const GLvoid*>(offset));
		}
	};
}