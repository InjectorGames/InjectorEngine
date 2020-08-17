#include <injector/graphics/gl_buffer.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	GlBuffer::GlBuffer(
		size_t size,
		BufferType type,
		BufferUsage usage,
		const void* data) :
		Buffer(size, type, usage)
	{
		glType = toGlType(type);
		glGenBuffers(GL_ONE, &buffer);
		glBindBuffer(glType, buffer);

		if (data)
		{
			Buffer::map(BufferAccess::WriteOnly);
			glBufferData(glType, static_cast<GLsizeiptr>(size), data, toGlUsage(usage));
			Buffer::unmap();
		}
		else
		{
			glBufferData(glType, static_cast<GLsizeiptr>(size), nullptr, toGlUsage(usage));
		}
		
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

	void* GlBuffer::map(BufferAccess access)
	{
		Buffer::map(access);
		glBindBuffer(glType, buffer);

		auto mappedData = glMapBufferRange(glType, 0,
			static_cast<GLsizeiptr>(size), toGlAccess(access));

		if (!mappedData)
			throw std::runtime_error("Failed to map OpenGL buffer");

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
			throw std::runtime_error("Failed to map OpenGL buffer");

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
				static_cast<GLintptr>(mapOffset), 
				static_cast<GLsizeiptr>(mapSize));
		}
		
		if(glUnmapBuffer(glType) == GL_FALSE)
			throw std::runtime_error("Failed to unmap OpenGL buffer");

		glBindBuffer(glType, GL_ZERO);
	}

	void GlBuffer::setData(const void* data, size_t _size)
	{
		if (_size > size)
			throw std::runtime_error("Out of OpenGL buffer range");

		Buffer::map(BufferAccess::WriteOnly, _size, 0);
		glBindBuffer(glType, buffer);
		glBufferSubData(glType, 0, static_cast<GLsizeiptr>(_size), data);
		glBindBuffer(glType, GL_ZERO);
		Buffer::unmap();
	}
	void GlBuffer::setData(const void* data, size_t _size, size_t offset)
	{
		if (_size + offset > size)
			throw std::runtime_error("Out of OpenGL buffer range");

		Buffer::map(BufferAccess::WriteOnly, _size, offset);
		glBindBuffer(glType, buffer);
		glBufferSubData(glType, static_cast<GLintptr>(offset),
			static_cast<GLsizeiptr>(_size), data);
		glBindBuffer(glType, GL_ZERO);
		Buffer::unmap();
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

	GLenum GlBuffer::toGlType(BufferType type)
	{
		// TODO: add other buffer types
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
			throw std::runtime_error("Unsupported OpenGL buffer type");
		}
	}
	BufferType GlBuffer::toType(GLenum type)
	{
		switch (type)
		{
		case GL_UNIFORM_BUFFER:
			return BufferType::Uniform;
		case GL_ELEMENT_ARRAY_BUFFER:
			return BufferType::Index;
		case GL_ARRAY_BUFFER:
			return BufferType::Vertex;
		case GL_TRANSFORM_FEEDBACK_BUFFER:
			return BufferType::TransformFeedback;
		default:
			throw std::runtime_error("Unsupported OpenGL buffer type");
		}
	}

	GLenum GlBuffer::toGlUsage(BufferUsage usage)
	{
		switch (usage)
		{
		case BufferUsage::CpuOnly:
			return GL_DYNAMIC_DRAW;
		case BufferUsage::GpuOnly:
			return GL_STATIC_DRAW;
		case BufferUsage::CpuToGpu:
			return GL_DYNAMIC_DRAW;
		case BufferUsage::GpuToCpu:
			return GL_DYNAMIC_READ;
		case BufferUsage::CpuCopy:
			return GL_DYNAMIC_READ; // TODOL test if this correct
		default:
			throw std::runtime_error("Unsupported OpenGL buffer usage");
		}
	}
	BufferUsage GlBuffer::toUsage(GLenum usage)
	{
		switch (usage)
		{
		case GL_STATIC_DRAW:
			return BufferUsage::GpuOnly;
		case GL_DYNAMIC_DRAW:
			return BufferUsage::CpuToGpu;
		case GL_DYNAMIC_READ:
			return BufferUsage::GpuToCpu;
		default:
			throw std::runtime_error("Unsupported OpenGL buffer usage");
		}
	}
}
