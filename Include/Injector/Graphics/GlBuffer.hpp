#pragma once
#include "Injector/Graphics/BufferAccess.hpp"
#include "GL/glew.h"

#include <cstdint>

namespace Injector::Graphics
{
	class GlBuffer
	{
	protected:
		GLuint buffer;
		size_t size;
		GLenum type;
		bool mappable;
		bool mapped;
		BufferAccess mapAccess;
		size_t mapSize;
		size_t mapOffset;
	public:
		GlBuffer(size_t size,
			GLenum type,
			GLenum usage,
			const void* data);
		virtual ~GlBuffer();

		GLuint getBuffer() const noexcept;
		size_t getSize() const noexcept;
		GLenum getType() const noexcept;
		bool isMappable() const noexcept;
		bool isMapped() const noexcept;
		BufferAccess getMapAccess() const noexcept;
		size_t getMapSize() const noexcept;
		size_t getMapOffset() const noexcept;

		void bind();
		void unbind();

		void flush(size_t size, size_t offset);

		void* map(BufferAccess access);
		void* map(BufferAccess access, size_t size, size_t offset);
		void unmap();

		void setData(const void* data, size_t size);
		void setData(const void* data, size_t size, size_t offset);

		static GLbitfield toGlAccess(BufferAccess access);
	};
}