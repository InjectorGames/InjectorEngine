#pragma once
#include "Injector/Graphics/Buffer.hpp"
#include "GL/glew.h"

#include <cstdint>

namespace Injector
{
	class GlBuffer : public Buffer
	{
	protected:
		GLuint buffer;
		GLenum glType;
	public:
		GlBuffer(BufferType type,
			size_t size,
			GLenum usage,
			const void* data);
		virtual ~GlBuffer();

		GLuint getBuffer() const noexcept;
		GLenum getGlType() const noexcept;

		void bind() noexcept;
		void unbind() noexcept;

		void* map(BufferAccess access) override;
		void* map(BufferAccess access, size_t size, size_t offset) override;
		void unmap() override;

		void setData(const void* data, size_t size) override;
		void setData(const void* data, size_t size, size_t offset) override;

		static GLenum toGlType(BufferType type);
		static bool isGlMappable(GLenum usage);
		static GLbitfield toGlAccess(BufferAccess access);
	};
}