#include <injector/gl_buffer.hpp>

#include <GL/glew.h>
#include <SDL_opengl.h>

namespace INJECTOR_NAMESPACE
{
	/*enum class Type : GLenum
	{
		Array = GL_ARRAY_BUFFER, // GL 2.0
		AtomicCounter = GL_ATOMIC_COUNTER_BUFFER, // GL 4.3
		CopyRead = GL_COPY_READ_BUFFER, // GL 3.1
		CopyWrite = GL_COPY_WRITE_BUFFER, // GL 2.0
		DispatchIndirect = GL_DISPATCH_INDIRECT_BUFFER, // GL 4.3
		DrawIndirect = GL_DRAW_INDIRECT_BUFFER, // GL 2.0
		ElementArray = GL_ELEMENT_ARRAY_BUFFER, // GL 2.0
		PixelPack = GL_PIXEL_PACK_BUFFER, // GL 2.0
		PixelUnpack = GL_PIXEL_UNPACK_BUFFER, // GL 2.0
		Query = GL_QUERY_BUFFER, // GL 4.4
		ShaderStorage = GL_SHADER_STORAGE_BUFFER, // GL 4.3
		Texture = GL_TEXTURE_BUFFER, // GL 3.1
		TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER, // GL 2.0
		Uniform = GL_UNIFORM_BUFFER, // GL 3.1
	};

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
	};*/

	uint32_t GlBuffer::create() noexcept
	{
		GLuint buffer;
		glGenBuffers(GL_ONE, &buffer);
		return static_cast<uint32_t>(buffer);
	}
	void GlBuffer::destroy(uint32_t buffer) noexcept
	{
		glDeleteBuffers(GL_ONE, static_cast<const GLuint*>(&buffer));
	}
	void GlBuffer::bind(uint32_t type, uint32_t buffer) noexcept
	{
		glBindBuffer(static_cast<GLenum>(type), static_cast<GLuint>(buffer));
	}

	void GlBuffer::setData(uint32_t type, uint32_t usage,
	const void* data, size_t size) noexcept
	{
		glBufferData(static_cast<GLenum>(type),
			static_cast<GLsizeiptr>(size),
			static_cast<const GLvoid*>(data),
			static_cast<GLenum>(usage));
	}
	void GlBuffer::setSubData(uint32_t type,
		const void* data, size_t size, size_t offset) noexcept
	{
		// TODO: add range check

		glBufferSubData(static_cast<GLenum>(type),
			static_cast<GLintptr>(offset),
			static_cast<GLsizeiptr>(size),
			static_cast<const GLvoid*>(data));
	}

	GlBuffer::GlBuffer(uint32_t _type, uint32_t _usage) :
		size(), type(_type), usage(_usage)
	{
		instance = create();
	}
	GlBuffer::~GlBuffer()
	{
		destroy(instance);
	}

	uint32_t GlBuffer::getInstance() const noexcept
	{
		return instance;
	}
	size_t GlBuffer::getSize() const noexcept
	{
		return size;
	}
	uint32_t GlBuffer::getType() const noexcept
	{
		return type;
	}
	uint32_t GlBuffer::getUsage() const noexcept
	{
		return usage;
	}

	void GlBuffer::bind() const noexcept
	{
		bind(type, instance);
	}
	void GlBuffer::unbind() const noexcept
	{
		bind(type, 0);
	}
}
