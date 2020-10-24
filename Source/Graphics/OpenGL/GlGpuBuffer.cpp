#include "Injector/Graphics/OpenGL/GlGpuBuffer.hpp"
#include "Injector/Exception/NullException.hpp"
#include "Injector/Exception/OutOfRangeException.hpp"
#include "Injector/Graphics/OpenGL/GlGpuBufferType.hpp"
#include "Injector/Graphics/OpenGL/GlGpuBufferAccess.hpp"

namespace Injector
{
	bool GlGpuBuffer::isGlMappable(
		GLenum usage)
	{
		return
			usage == GL_DYNAMIC_DRAW ||
			usage == GL_DYNAMIC_READ ||
			usage == GL_STREAM_DRAW ||
			usage == GL_STREAM_READ;
	}

	GlGpuBuffer::GlGpuBuffer(
		GpuBufferType type,
		size_t size,
		GLenum usage,
		const void* data) :
		GpuBuffer(type, size, isGlMappable(usage)),
		glType(toGlGpuBufferType(type))
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
				std::string(typeid(GlGpuBuffer).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Buffer is not mappable");
		}
		if (mapped)
		{
			throw Exception(
				std::string(typeid(GlGpuBuffer).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Buffer is already mapped");
		}

		glBindBuffer(glType, buffer);

		auto mappedData = glMapBufferRange(
			glType,
			0,
			static_cast<GLsizeiptr>(size),
			toGlGpuBufferAccess(access));

		if (!mappedData)
		{
			throw Exception(
				std::string(typeid(GlGpuBuffer).name()),
				std::string(__func__),
				std::to_string(__LINE__),
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
				std::string(typeid(GlGpuBuffer).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Buffer is not mappable");
		}
		if (mapped)
		{
			throw Exception(
				std::string(typeid(GlGpuBuffer).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Buffer is already mapped");
		}
		if (_size + offset > size)
		{
			throw OutOfRangeException(
				std::string(typeid(GlGpuBuffer).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				static_cast<uint64_t>(_size + offset),
				static_cast<uint64_t>(size));
		}

		glBindBuffer(glType, buffer);

		auto mappedData = glMapBufferRange(
			glType,
			static_cast<GLintptr>(offset),
			static_cast<GLsizeiptr>(_size),
			toGlGpuBufferAccess(access));

		if (!mappedData)
		{
			throw Exception(
				std::string(typeid(GlGpuBuffer).name()),
				std::string(__func__),
				std::to_string(__LINE__),
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
				std::string(typeid(GlGpuBuffer).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Buffer is not mapped");
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
				std::string(typeid(GlGpuBuffer).name()),
				std::string(__func__),
				std::to_string(__LINE__),
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
				std::string(typeid(GlGpuBuffer).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Buffer is not mappable");
		}
		if (mapped)
		{
			throw Exception(
				std::string(typeid(GlGpuBuffer).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Buffer is already mapped");
		}
		if(!data)
		{
			throw NullException(
				std::string(typeid(GlGpuBuffer).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"data");
		}
		if (_size > size)
		{
			throw OutOfRangeException(
				std::string(typeid(GlGpuBuffer).name()),
				std::string(__func__),
				std::to_string(__LINE__),
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
				std::string(typeid(GlGpuBuffer).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Buffer is not mappable");
		}
		if (mapped)
		{
			throw Exception(
				std::string(typeid(GlGpuBuffer).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Buffer is already mapped");
		}
		if(!data)
		{
			throw NullException(
				std::string(typeid(GlGpuBuffer).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"data");
		}
		if (_size + offset > size)
		{
			throw OutOfRangeException(
				std::string(typeid(GlGpuBuffer).name()),
				std::string(__func__),
				std::to_string(__LINE__),
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
}
