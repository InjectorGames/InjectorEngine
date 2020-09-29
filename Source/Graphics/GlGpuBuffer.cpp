#include "Injector/Graphics/GlGpuBuffer.hpp"
#include "Injector/Exception/NullException.hpp"
#include "Injector/Exception/OutOfRangeException.hpp"

namespace Injector
{
	GlGpuBuffer::GlGpuBuffer(
		GpuBufferType type,
		size_t size,
		GLenum usage,
		const void* data) :
		GpuBuffer(type, size, isGlMappable(usage)),
		glType(toGlType(type))
	{
		glGenBuffers(GL_ONE, &buffer);
		glBindBuffer(glType, buffer);
		glBufferData(glType, static_cast<GLsizeiptr>(size), data, usage);
		glBindBuffer(glType, GL_ZERO);
	}
	GlGpuBuffer::~GlGpuBuffer()
	{
		glDeleteBuffers(GL_ONE, &buffer);
	}

	GLuint GlGpuBuffer::getBuffer() const noexcept
	{
		return buffer;
	}
	GLenum GlGpuBuffer::getGlType() const noexcept
	{
		return glType;
	}

	void GlGpuBuffer::bind() noexcept
	{
		glBindBuffer(glType, buffer);
	}
	void GlGpuBuffer::unbind() noexcept
	{
		glBindBuffer(glType, GL_ZERO);
	}

	void* GlGpuBuffer::map(
		GpuBufferAccess access)
	{
		if (!mappable)
		{
			throw Exception(
				"GlGpuBuffer",
				"map",
				"Not mappable");
		}
		if (mapped)
		{
			throw Exception(
				"GlGpuBuffer",
				"map",
				"Already mapped");
		}

		glBindBuffer(glType, buffer);

		auto mappedData = glMapBufferRange(
			glType,
			0,
			static_cast<GLsizeiptr>(size),
			toGlAccess(access));

		if (!mappedData)
		{
			throw Exception(
				"GlGpuBuffer",
				"map",
				"Failed to map buffer");
		}

		glBindBuffer(glType, GL_ZERO);

		mapped = true;
		mapAccess = access;
		mapSize = size;
		mapOffset = 0;
		return mappedData;
	}
	void* GlGpuBuffer::map(
		GpuBufferAccess access,
		size_t _size,
		size_t offset)
	{
		if (!mappable)
		{
			throw Exception(
				"GlGpuBuffer",
				"map",
				"Not mappable");
		}
		if (mapped)
		{
			throw Exception(
				"GlGpuBuffer",
				"map",
				"Already mapped");
		}
		if (_size + offset > size)
		{
			throw OutOfRangeException(
				"GlGpuBuffer",
				"map",
				static_cast<uint64_t>(_size + offset),
				static_cast<uint64_t>(size));
		}

		glBindBuffer(glType, buffer);

		auto mappedData = glMapBufferRange(
			glType,
			static_cast<GLintptr>(offset),
			static_cast<GLsizeiptr>(_size),
			toGlAccess(access));

		if (!mappedData)
		{
			throw Exception(
				"GlGpuBuffer",
				"map",
				"Failed to map buffer");
		}

		glBindBuffer(glType, GL_ZERO);

		mapped = true;
		mapAccess = access;
		mapSize = _size;
		mapOffset = offset;
		return mappedData;
	}
	void GlGpuBuffer::unmap()
	{
		if (!mapped)
		{
			throw Exception(
				"GlGpuBuffer",
				"map",
				"Not mapped");
		}

		glBindBuffer(glType, buffer);

		if (mapAccess == GpuBufferAccess::WriteOnly ||
			mapAccess == GpuBufferAccess::ReadWrite)
		{
			glFlushMappedBufferRange(
				glType,
				static_cast<GLintptr>(mapSize),
				static_cast<GLsizeiptr>(mapOffset));
		}

		if (glUnmapBuffer(glType) == GL_FALSE)
		{
			throw Exception(
				"GlGpuBuffer",
				"unmap",
				"Failed to unmap buffer");
		}

		glBindBuffer(glType, GL_ZERO);
		mapped = false;
	}

	void GlGpuBuffer::setData(
		const void* data,
		size_t _size)
	{
		if (!mappable)
		{
			throw Exception(
				"GlGpuBuffer",
				"setData",
				"Not mappable");
		}
		if (mapped)
		{
			throw Exception(
				"GlGpuBuffer",
				"setData",
				"Already mapped");
		}
		if(!data)
		{
			throw NullException(
				"GlGpuBuffer",
				"setData",
				"data");
		}
		if (_size > size)
		{
			throw OutOfRangeException(
				"GlGpuBuffer",
				"setData",
				static_cast<uint64_t>(_size),
				static_cast<uint64_t>(size));
		}

		glBindBuffer(glType, buffer);

		glBufferSubData(
			glType,
			0,
			static_cast<GLsizeiptr>(_size),
			data);

		glBindBuffer(glType, GL_ZERO);
	}
	void GlGpuBuffer::setData(
		const void* data,
		size_t _size,
		size_t offset)
	{
		if (!mappable)
		{
			throw Exception(
				"GlGpuBuffer",
				"setData",
				"Not mappable");
		}
		if (mapped)
		{
			throw Exception(
				"GlGpuBuffer",
				"setData",
				"Already mapped");
		}
		if(!data)
		{
			throw NullException(
				"GlGpuBuffer",
				"setData",
				"data");
		}
		if (_size + offset > size)
		{
			throw OutOfRangeException(
				"GlGpuBuffer",
				"setData",
				static_cast<uint64_t>(_size + offset),
				static_cast<uint64_t>(size));
		}

		glBindBuffer(glType, buffer);

		glBufferSubData(
			glType,
			static_cast<GLintptr>(offset),
			static_cast<GLsizeiptr>(_size),
			data);

		glBindBuffer(glType, GL_ZERO);
	}

	GLenum GlGpuBuffer::toGlType(GpuBufferType type)
	{
		switch (type)
		{
		case GpuBufferType::Uniform:
			return GL_UNIFORM_BUFFER;
		case GpuBufferType::Index:
			return GL_ELEMENT_ARRAY_BUFFER;
		case GpuBufferType::Vertex:
			return GL_ARRAY_BUFFER;
		case GpuBufferType::TransformFeedback:
			return GL_TRANSFORM_FEEDBACK_BUFFER;
		default:
			throw Exception(
				"GlGpuBuffer",
				"toGlType",
				"Unsupported type");
		}
	}
	bool GlGpuBuffer::isGlMappable(GLenum usage)
	{
		return
			usage == GL_DYNAMIC_DRAW ||
			usage == GL_DYNAMIC_READ ||
			usage == GL_STREAM_DRAW ||
			usage == GL_STREAM_READ;
	}
	GLbitfield GlGpuBuffer::toGlAccess(GpuBufferAccess access)
	{
		if (access == GpuBufferAccess::ReadOnly)
			return GL_MAP_READ_BIT;
		else if (access == GpuBufferAccess::WriteOnly)
			return GL_MAP_WRITE_BIT |
				   GL_MAP_FLUSH_EXPLICIT_BIT |
				   GL_MAP_INVALIDATE_RANGE_BIT; //TODO: Check if this correct
		else if (access == GpuBufferAccess::ReadWrite)
			return GL_MAP_READ_BIT |
				   GL_MAP_WRITE_BIT |
				   GL_MAP_FLUSH_EXPLICIT_BIT;
		else
			throw Exception(
				"GlGpuBuffer",
				"toGlAccess",
				"Unsupported access");
	}
}
