#pragma once
#include <injector/graphics/buffer.hpp>

#include <GL/glew.h>
#include <SDL_opengl.h>

#include <vector>
#include <cstdint>

namespace INJECTOR_NAMESPACE
{
	class GlBuffer : public Buffer
	{
	protected:
		GLuint buffer;
		GLenum glType;
		GLbitfield glAccess;
	public:
		GlBuffer(size_t size,
			BufferType type,
			BufferUsage usage,
			const void* data = nullptr);
		virtual ~GlBuffer();

		GLuint getBuffer() const noexcept;

		void* map(BufferAccess access) override;
		void* map(BufferAccess access, size_t size, size_t offset) override;
		void unmap() override;

		void setData(const void* data, size_t size) override;
		void setData(const void* data, size_t size, size_t offset) override;

		static GLbitfield toGlAccess(BufferAccess access);

		static GLenum toGlType(BufferType type);
		static BufferType toType(GLenum type);

		static GLenum toGlUsage(BufferUsage usage);
		static BufferUsage toUsage(GLenum usage);
	};

	using GlBufferHandle = std::shared_ptr<GlBuffer>;
}