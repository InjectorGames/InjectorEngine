#include "Injector/Graphics/GlBuffer.hpp"
#include "Injector/Exception/OutOfRangeException.hpp"

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
			throw Exception("GlBuffer", "map", "Failed to map buffer");

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
			throw Exception("GlBuffer", "map", "Failed to map buffer");

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
			throw Exception("GlBuffer", "unmap", "Failed to unmap buffer");

		glBindBuffer(glType, GL_ZERO);
	}

	void GlBuffer::setData(const void* data, size_t _size)
	{
		if (!mappable)
			throw Exception("GlBuffer", "setData", "Not mappable");
		if (mapped)
			throw Exception("GlBuffer", "setData", "Already mapped");
		if (_size > size)
			throw OutOfRangeException("GlBuffer", "setData", _size, size);

		glBindBuffer(glType, buffer);
		glBufferSubData(glType, 0, static_cast<GLsizeiptr>(_size), data);
		glBindBuffer(glType, GL_ZERO);
	}
	void GlBuffer::setData(const void* data, size_t _size, size_t offset)
	{
		if (!mappable)
			throw Exception("GlBuffer", "setData", "Not mappable");
		if (mapped)
			throw Exception("GlBuffer", "setData", "Already mapped");
		if (_size + offset > size)
			throw OutOfRangeException("GlBuffer", "setData", _size + offset, size);

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
			throw Exception("GlBuffer", "toGlType", "Unsupported type");
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
			throw Exception("GlBuffer", "toGlAccess", "Unsupported access");
	}
}
