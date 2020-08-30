#include <injector/graphics/gl_buffer.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	GlBuffer::GlBuffer(
		size_t _size,
		GLenum _type,
		GLenum usage,
		const void* data) :
		size(_size),
		type(_type),
		mapped(false),
		mapAccess(),
		mapSize(),
		mapOffset()
	{
		glGenBuffers(GL_ONE, &buffer);
		glBindBuffer(_type, buffer);
		glBufferData(type, static_cast<GLsizeiptr>(size), data, usage);
		glBindBuffer(type, GL_ZERO);

		mappable =
			usage == GL_DYNAMIC_DRAW ||
			usage == GL_DYNAMIC_READ ||
			usage == GL_STREAM_DRAW || 
			usage == GL_STREAM_READ;
	}
	GlBuffer::~GlBuffer()
	{
		glDeleteBuffers(GL_ONE, &buffer);
	}

	GLuint GlBuffer::getBuffer() const noexcept
	{
		return buffer;
	}
	size_t GlBuffer::getSize() const noexcept
	{
		return size;
	}
	GLenum GlBuffer::getType() const noexcept
	{
		return type;
	}
	bool GlBuffer::isMappable() const noexcept
	{
		return mappable;
	}
	bool GlBuffer::isMapped() const noexcept
	{
		return mapped;
	}
	BufferAccess GlBuffer::getMapAccess() const noexcept
	{
		return mapAccess;
	}
	size_t GlBuffer::getMapSize() const noexcept
	{
		return mapSize;
	}
	size_t GlBuffer::getMapOffset() const noexcept
	{
		return mapOffset;
	}

	void GlBuffer::bind()
	{
		glBindBuffer(type, buffer);
	}
	void GlBuffer::unbind()
	{
		glBindBuffer(type, GL_ZERO);
	}

	void GlBuffer::flush(size_t size, size_t offset)
	{
		glFlushMappedBufferRange(type,
			static_cast<GLintptr>(offset),
			static_cast<GLsizeiptr>(size));
	}

	void* GlBuffer::map(BufferAccess access)
	{
		if (!mappable)
			throw std::runtime_error("Failed to map OpenGL buffer, not mappable");
		if (mapped)
			throw std::runtime_error("Failed to map OpenGL buffer, already mapped");

		glBindBuffer(type, buffer);

		auto mappedData = glMapBufferRange(type, 0,
			static_cast<GLsizeiptr>(size), toGlAccess(access));

		if (!mappedData)
			throw std::runtime_error("Failed to map OpenGL buffer");

		glBindBuffer(type, GL_ZERO);

		mapped = true;
		mapAccess = access;
		mapSize = size;
		mapOffset = 0;

		return mappedData;
	}
	void* GlBuffer::map(BufferAccess access, size_t _size, size_t offset)
	{
		if (!mappable)
			throw std::runtime_error("Failed to map OpenGL buffer, not mappable");
		if (mapped)
			throw std::runtime_error("Failed to map OpenGL buffer, already mapped");
		if (_size + offset > size)
			throw std::runtime_error("Failed to map OpenGL buffer, out of range");

		glBindBuffer(type, buffer);

		auto mappedData = glMapBufferRange(type, static_cast<GLintptr>(offset),
			static_cast<GLsizeiptr>(size), toGlAccess(access));

		if (!mappedData)
			throw std::runtime_error("Failed to map OpenGL buffer");

		glBindBuffer(type, GL_ZERO);

		mapped = true;
		mapAccess = access;
		mapSize = _size;
		mapOffset = offset;

		return mappedData;
	}
	void GlBuffer::unmap()
	{
		if (!mapped)
			throw std::runtime_error("Failed to unmap OpenGL buffer, not mapped");

		glBindBuffer(type, buffer);

		if (mapAccess == BufferAccess::WriteOnly || mapAccess == BufferAccess::ReadWrite)
			flush(mapSize, mapOffset);
		
		if(glUnmapBuffer(type) == GL_FALSE)
			throw std::runtime_error("Failed to unmap OpenGL buffer");

		glBindBuffer(type, GL_ZERO);
		mapped = false;
	}

	void GlBuffer::setData(const void* data, size_t _size)
	{
		if (!mappable)
			throw std::runtime_error("Failed to set Vulkan buffer data, not mappable");
		if (mapped)
			throw std::runtime_error("Failed to set Vulkan buffer data, already mapped");
		if (_size > size)
			throw std::runtime_error("Failed to map OpenGL buffer, out of range");

		glBindBuffer(type, buffer);
		glBufferSubData(type, 0, static_cast<GLsizeiptr>(_size), data);
		glBindBuffer(type, GL_ZERO);
	}
	void GlBuffer::setData(const void* data, size_t _size, size_t offset)
	{
		if (!mappable)
			throw std::runtime_error("Failed to set OpenGL buffer data, not mappable");
		if (mapped)
			throw std::runtime_error("Failed to set OpenGL buffer data, already mapped");
		if (_size + offset > size)
			throw std::runtime_error("Failed to map OpenGL buffer, out of range");

		glBindBuffer(type, buffer);
		glBufferSubData(type, static_cast<GLintptr>(offset),
			static_cast<GLsizeiptr>(_size), data);
		glBindBuffer(type, GL_ZERO);
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
			throw std::runtime_error("Unsupported OpenGL buffer access type");
	}
}
