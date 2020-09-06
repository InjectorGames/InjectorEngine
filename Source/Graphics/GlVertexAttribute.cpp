#include "Injector/Graphics/GlVertexAttribute.hpp"

namespace Injector::Graphics
{
	GlVertexAttribute::GlVertexAttribute(
		const GLuint _index,
		const GLint _size,
		const GLenum _type,
		const bool _normalized,
		const size_t _stride,
		const size_t _offset) :
		index(_index),
		size(_size),
		type(_type),
		normalized(_normalized),
		stride(_stride),
		offset(_offset)
	{}

	void GlVertexAttribute::enable() const noexcept
	{
		glEnableVertexAttribArray(index);
	}
	void GlVertexAttribute::disable() const noexcept
	{
		glDisableVertexAttribArray(index);
	}

	void GlVertexAttribute::setPointer() const noexcept
	{
		glVertexAttribPointer(index, size, type, normalized ? GL_TRUE : GL_FALSE,
			static_cast<GLsizei>(stride), reinterpret_cast<const GLvoid*>(offset));
	}
}
