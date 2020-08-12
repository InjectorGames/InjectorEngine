#include <injector/graphics/gl_buffer.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	GLbitfield GlBuffer::getGlAccess(BufferAccess access)
	{
		if (access == BufferAccess::ReadOnly)
			return GL_MAP_READ_BIT;
		else if (access == BufferAccess::WriteOnly)
			return GL_MAP_WRITE_BIT |
			GL_MAP_FLUSH_EXPLICIT_BIT | 
			GL_MAP_INVALIDATE_RANGE_BIT; //TODO: Check if this correct
		else if (access == BufferAccess::ReadWrite)
			return GL_MAP_READ_BIT | 
			GL_MAP_WRITE_BIT | 
			GL_MAP_FLUSH_EXPLICIT_BIT;
		else
			throw std::runtime_error("Unsupported OpenGL buffer access type");
	}

	GlBuffer::GlBuffer(GLenum _type, GLenum _usage, size_t size) :
		Buffer(size),
		type(_type),
		usage(_usage)
	{
		glGenBuffers(GL_ONE, &buffer);
		glBindBuffer(type, buffer);
		glBufferData(type, static_cast<GLsizeiptr>(size), nullptr, usage);
		glBindBuffer(type, GL_ZERO);
	}
	GlBuffer::~GlBuffer()
	{
		glDeleteBuffers(GL_ONE, &buffer);
	}

	void* GlBuffer::map(BufferAccess access)
	{
		Buffer::map(access);

		glBindBuffer(type, buffer);
		auto mappedData = glMapBufferRange(type,
			static_cast<GLintptr>(0),
			static_cast<GLsizeiptr>(size),
			getGlAccess(access));
		if (!mappedData)
			throw std::runtime_error("Failed to map OpenGL buffer");
		glBindBuffer(type, GL_ZERO);
		return mappedData;
	}
	void* GlBuffer::map(BufferAccess access, size_t size, size_t offset)
	{
		Buffer::map(access);

		glBindBuffer(type, buffer);
		auto mappedData = glMapBufferRange(type,
			static_cast<GLintptr>(offset),
			static_cast<GLsizeiptr>(size),
			getGlAccess(access));
		if (!mappedData)
			throw std::runtime_error("Failed to map OpenGL buffer");
		glBindBuffer(type, GL_ZERO);
		return mappedData;
	}
	void GlBuffer::unmap()
	{
		glBindBuffer(type, buffer);

		if (mapAccess == BufferAccess::WriteOnly || mapAccess == BufferAccess::ReadWrite)
		{
			glFlushMappedBufferRange(type,
				static_cast<GLintptr>(mapOffset), 
				static_cast<GLsizeiptr>(mapSize));
		}
		
		if(glUnmapBuffer(type) == GL_FALSE)
			throw std::runtime_error("Failed to unmap OpenGL buffer");
		glBindBuffer(type, GL_ZERO);
	}

	void GlBuffer::setData(const void* data, size_t _size)
	{
		if (_size > size)
			throw std::runtime_error("Out of OpenGL buffer range");

		glBindBuffer(type, buffer);
		glBufferSubData(type,
			static_cast<GLintptr>(0),
			static_cast<GLsizeiptr>(_size),
			static_cast<const GLvoid*>(data));
		glBindBuffer(type, GL_ZERO);
	}
	void GlBuffer::setData(const void* data, size_t _size, size_t offset)
	{
		if (_size + offset > size)
			throw std::runtime_error("Out of OpenGL buffer range");

		glBindBuffer(type, buffer);
		glBufferSubData(type,
			static_cast<GLintptr>(offset),
			static_cast<GLsizeiptr>(_size),
			static_cast<const GLvoid*>(data));
		glBindBuffer(type, GL_ZERO);
	}

	GLuint GlBuffer::getBuffer() const noexcept
	{
		return buffer;
	}
	GLenum GlBuffer::getType() const noexcept
	{
		return type;
	}
	GLenum GlBuffer::getUsage() const noexcept
	{
		return usage;
	}
}
