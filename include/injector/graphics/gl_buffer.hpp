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
	public:
		enum class Usage : GLenum
		{
			// STREAM: The data store contents will be modified once and used at most a few times.
			// STATIC: The data store contents will be modified once and used many times.
			// DYNAMIC: The data store contents will be modified repeatedly and used many times.
			// DRAW: The data store contents are modified by the application, and used as the source for GL drawing and image specification commands.
			// READ: The data store contents are modified by reading data from the GL, and used to return that data when queried by the application.
			// COPY: The data store contents are modified by reading data from the GL, and used as the source for GL drawing and image specification commands.

			StreamDraw = GL_STREAM_DRAW,
			StreamRead = GL_STREAM_READ,
			StreamCopy = GL_STREAM_COPY,
			StaticDraw = GL_STATIC_DRAW,
			StaticRead = GL_STATIC_READ,
			StaticCopy = GL_STATIC_COPY,
			DynamicDraw = GL_DYNAMIC_DRAW,
			DynamicRead = GL_DYNAMIC_READ,
			DynamicCopy = GL_DYNAMIC_COPY,
		};
	protected:
		GLuint buffer;
		GLuint usage;

		static GLbitfield getGlAccess(BufferAccess access);
	public:
		GlBuffer(size_t size, GLenum usage);
		virtual ~GlBuffer();

		BufferUsage getUsage() const override;
		GLuint getBuffer() const noexcept;

		void* map(BufferAccess access) override;
		void* map(BufferAccess access, size_t size, size_t offset) override;
		void unmap() override;

		void setData(const void* data, size_t size) override;
		void setData(const void* data, size_t size, size_t offset) override;

		static GLenum toGlUsage(BufferUsage usage);
		static BufferUsage toUsage(GLenum usage);
	};

	using GlBufferHandle = std::shared_ptr<GlBuffer>;
}