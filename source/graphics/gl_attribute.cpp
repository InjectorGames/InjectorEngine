#include <injector/graphics/gl_attribute.hpp>

namespace INJECTOR_NAMESPACE
{
	GlAttribute::GlAttribute(
		const uint32_t _index,
		const Size _size,
		const Type _type,
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

	void GlAttribute::enable() const noexcept
	{
		glEnableVertexAttribArray(static_cast<GLuint>(index));
	}
	void GlAttribute::disable() const noexcept
	{
		glDisableVertexAttribArray(static_cast<GLuint>(index));
	}

	void GlAttribute::setPointer() const noexcept
	{
		glVertexAttribPointer(
			static_cast<GLuint>(index),
			static_cast<GLint>(size),
			static_cast<GLenum>(type),
			normalized ? GL_TRUE : GL_FALSE,
			static_cast<GLsizei>(stride),
			reinterpret_cast<const GLvoid*>(offset));
	}
}
