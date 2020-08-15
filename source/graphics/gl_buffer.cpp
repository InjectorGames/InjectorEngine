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

	GlBuffer::GlBuffer(size_t size, GLenum _usage) :
		Buffer(size),
		usage(_usage)
	{
		glGenBuffers(GL_ONE, &buffer);
		glBindBuffer(_usage, buffer);
		glBufferData(_usage, static_cast<GLsizeiptr>(size), nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(_usage, GL_ZERO);
	}
	GlBuffer::~GlBuffer()
	{
		glDeleteBuffers(GL_ONE, &buffer);
	}

	GLuint GlBuffer::getBuffer() const noexcept
	{
		return buffer;
	}

	void* GlBuffer::map(BufferAccess access)
	{
		Buffer::map(access);

		glBindBuffer(usage, buffer);
		auto mappedData = glMapBufferRange(usage,
			static_cast<GLintptr>(0),
			static_cast<GLsizeiptr>(size),
			getGlAccess(access));
		if (!mappedData)
			throw std::runtime_error("Failed to map OpenGL buffer");
		glBindBuffer(usage, GL_ZERO);
		return mappedData;
	}
	void* GlBuffer::map(BufferAccess access, size_t size, size_t offset)
	{
		Buffer::map(access);

		glBindBuffer(usage, buffer);
		auto mappedData = glMapBufferRange(usage,
			static_cast<GLintptr>(offset),
			static_cast<GLsizeiptr>(size),
			getGlAccess(access));
		if (!mappedData)
			throw std::runtime_error("Failed to map OpenGL buffer");
		glBindBuffer(usage, GL_ZERO);
		return mappedData;
	}
	void GlBuffer::unmap()
	{
		glBindBuffer(usage, buffer);

		if (mapAccess == BufferAccess::WriteOnly || mapAccess == BufferAccess::ReadWrite)
		{
			glFlushMappedBufferRange(usage,
				static_cast<GLintptr>(mapOffset), 
				static_cast<GLsizeiptr>(mapSize));
		}
		
		if(glUnmapBuffer(usage) == GL_FALSE)
			throw std::runtime_error("Failed to unmap OpenGL buffer");
		glBindBuffer(usage, GL_ZERO);
	}

	void GlBuffer::setData(const void* data, size_t _size)
	{
		if (_size > size)
			throw std::runtime_error("Out of OpenGL buffer range");

		glBindBuffer(usage, buffer);
		glBufferSubData(usage,
			static_cast<GLintptr>(0),
			static_cast<GLsizeiptr>(_size),
			static_cast<const GLvoid*>(data));
		glBindBuffer(usage, GL_ZERO);
	}
	void GlBuffer::setData(const void* data, size_t _size, size_t offset)
	{
		if (_size + offset > size)
			throw std::runtime_error("Out of OpenGL buffer range");

		glBindBuffer(usage, buffer);
		glBufferSubData(usage,
			static_cast<GLintptr>(offset),
			static_cast<GLsizeiptr>(_size),
			static_cast<const GLvoid*>(data));
		glBindBuffer(usage, GL_ZERO);
	}

	GLenum GlBuffer::toGlUsage(BufferUsage usage)
	{
		// TODO: add other buffer types
		switch (usage)
		{
		case BufferUsage::Uniform:
			return GL_UNIFORM_BUFFER;
		case BufferUsage::Index:
			return GL_ELEMENT_ARRAY_BUFFER;
		case BufferUsage::Vertex:
			return GL_ARRAY_BUFFER;
		case BufferUsage::TransformFeedback:
			return GL_TRANSFORM_FEEDBACK_BUFFER;
		default:
			throw std::runtime_error("Unsupported OpenGL buffer usage");
		}
	}
	BufferUsage GlBuffer::toUsage(GLenum usage)
	{
		switch (usage)
		{
		case GL_UNIFORM_BUFFER:
			return BufferUsage::Uniform;
		case GL_ELEMENT_ARRAY_BUFFER:
			return BufferUsage::Index;
		case GL_ARRAY_BUFFER:
			return BufferUsage::Vertex;
		case GL_TRANSFORM_FEEDBACK_BUFFER:
			return BufferUsage::TransformFeedback;
		default:
			throw std::runtime_error("Unsupported OpenGL buffer usage");
		}
	}
}
