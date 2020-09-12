#include "Injector/Graphics/GlBuffer.hpp"
#include "Injector/Graphics/GraphicsException.hpp"

namespace Injector
{
	GlBuffer::GlBuffer(
		BufferType type,
		size_t size,
		GLenum usage,
		const void* data) :
		Buffer(type, size, isGlMappable(usage)),
		glType(toGlType(type))
	{
		glGenBuffers(GL_ONE, &buffer);
		glBindBuffer(glType, buffer);
		glBufferData(glType, static_cast<GLsizeiptr>(size), data, usage);
		glBindBuffer(glType, GL_ZERO);
	}
	GlBuffer::~GlBuffer()
	{
		glDeleteBuffers(GL_ONE, &buffer);
	}

	GLuint GlBuffer::getBuffer() const noexcept
	{
		return buffer;
	}
	GLenum GlBuffer::getGlType() const noexcept
	{
		return glType;
	}

	void GlBuffer::bind() noexcept
	{
		glBindBuffer(glType, buffer);
	}
	void GlBuffer::unbind() noexcept
	{
		glBindBuffer(glType, GL_ZERO);
	}

	void* GlBuffer::map(BufferAccess access)
	{
		Buffer::map(access);
		glBindBuffer(glType, buffer);

		auto mappedData = glMapBufferRange(glType, 0,
			static_cast<GLsizeiptr>(size), toGlAccess(access));

		if (!mappedData)
			throw GraphicsException("Failed to map OpenGL buffer");

		glBindBuffer(glType, GL_ZERO);
		return mappedData;
	}
	void* GlBuffer::map(BufferAccess access, size_t size, size_t offset)
	{
		Buffer::map(access, size, offset);
		glBindBuffer(glType, buffer);

		auto mappedData = glMapBufferRange(glType, static_cast<GLintptr>(offset),
			static_cast<GLsizeiptr>(size), toGlAccess(access));

		if (!mappedData)
			throw GraphicsException("Failed to map OpenGL buffer");

		glBindBuffer(glType, GL_ZERO);
		return mappedData;
	}
	void GlBuffer::unmap()
	{
		Buffer::unmap();
		glBindBuffer(glType, buffer);

		if (mapAccess == BufferAccess::WriteOnly || mapAccess == BufferAccess::ReadWrite)
		{
			glFlushMappedBufferRange(glType,
				static_cast<GLintptr>(mapSize),
				static_cast<GLsizeiptr>(mapOffset));
		}
		
		if(glUnmapBuffer(glType) == GL_FALSE)
			throw GraphicsException("Failed to unmap OpenGL buffer");

		glBindBuffer(glType, GL_ZERO);
	}

	void GlBuffer::setData(const void* data, size_t _size)
	{
		if (!mappable)
			throw GraphicsException("Failed to set Vulkan buffer data, not mappable");
		if (mapped)
			throw GraphicsException("Failed to set Vulkan buffer data, already mapped");
		if (_size > size)
			throw GraphicsException("Failed to map OpenGL buffer, out of range");

		glBindBuffer(glType, buffer);
		glBufferSubData(glType, 0, static_cast<GLsizeiptr>(_size), data);
		glBindBuffer(glType, GL_ZERO);
	}
	void GlBuffer::setData(const void* data, size_t _size, size_t offset)
	{
		if (!mappable)
			throw GraphicsException("Failed to set OpenGL buffer data, not mappable");
		if (mapped)
			throw GraphicsException("Failed to set OpenGL buffer data, already mapped");
		if (_size + offset > size)
			throw GraphicsException("Failed to map OpenGL buffer, out of range");

		glBindBuffer(glType, buffer);
		glBufferSubData(glType, static_cast<GLintptr>(offset),
			static_cast<GLsizeiptr>(_size), data);
		glBindBuffer(glType, GL_ZERO);
	}

	GLenum GlBuffer::toGlType(BufferType type)
	{
		switch (type)
		{
		case BufferType::Uniform:
			return GL_UNIFORM_BUFFER;
		case BufferType::Index:
			return GL_ELEMENT_ARRAY_BUFFER;
		case BufferType::Vertex:
			return GL_ARRAY_BUFFER;
		case BufferType::TransformFeedback:
			return GL_TRANSFORM_FEEDBACK_BUFFER;
		default:
			throw GraphicsException("Unsupported OpenGL buffer type");
		}
	}
	bool GlBuffer::isGlMappable(GLenum usage)
	{
		return
			usage == GL_DYNAMIC_DRAW ||
			usage == GL_DYNAMIC_READ ||
			usage == GL_STREAM_DRAW || 
			usage == GL_STREAM_READ;
	}
	GLbitfield GlBuffer::toGlAccess(BufferAccess access)
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
			throw GraphicsException("Unsupported OpenGL buffer access type");
	}
}
