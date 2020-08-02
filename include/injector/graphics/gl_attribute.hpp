#pragma once
#include <injector/defines.hpp>
#include <cstdint>

#include <GL/glew.h>
#include <SDL_opengl.h>

namespace INJECTOR_NAMESPACE
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
		enum class Size : int
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
		size_t stride;
		size_t offset;

		GlAttribute(
			const uint32_t index,
			const Size size,
			const Type type,
			const bool normalized,
			const size_t stride,
			const size_t offset);

		void enable() const noexcept;
		void disable() const noexcept;
		void setPointer() const noexcept;
	};
}
