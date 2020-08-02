#include <injector/graphics/gl_buffer.hpp>

namespace INJECTOR_NAMESPACE
{
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
	void GlBuffer::bind(Type type, uint32_t buffer) noexcept
	{
		glBindBuffer(static_cast<GLenum>(type), static_cast<GLuint>(buffer));
	}

	void GlBuffer::setData(Type type, Usage usage,
	const void* data, size_t size) noexcept
	{
		glBufferData(static_cast<GLenum>(type),
			static_cast<GLsizeiptr>(size),
			static_cast<const GLvoid*>(data),
			static_cast<GLenum>(usage));
	}
	void GlBuffer::setSubData(Type type,
		const void* data, size_t size, size_t offset) noexcept
	{
		// TODO: add range check

		glBufferSubData(static_cast<GLenum>(type),
			static_cast<GLintptr>(offset),
			static_cast<GLsizeiptr>(size),
			static_cast<const GLvoid*>(data));
	}

	GlBuffer::GlBuffer(Type _type, Usage _usage) :
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
	GlBuffer::Type GlBuffer::getType() const noexcept
	{
		return type;
	}
	GlBuffer::Usage GlBuffer::getUsage() const noexcept
	{
		return usage;
	}

	void GlBuffer::bind() noexcept
	{
		bind(type, instance);
	}
	void GlBuffer::unbind() noexcept
	{
		bind(type, GL_ZERO);
	}
}
