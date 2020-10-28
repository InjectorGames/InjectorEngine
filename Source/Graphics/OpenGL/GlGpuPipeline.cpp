#include "Injector/Graphics/OpenGL/GlGpuPipeline.hpp"
#include "Injector/Exception/Exception.hpp"
#include "Injector/Graphics/OpenGL/GlGpuDrawMode.hpp"

namespace Injector
{
	bool GlGpuPipeline::getLinkStatus(
		GLuint program) noexcept
	{
		GLint success;

		glGetProgramiv(
			program,
			GL_LINK_STATUS,
			&success);

		return success == GL_TRUE;
	}
	std::string GlGpuPipeline::getInfoLog(
		GLuint program) noexcept
	{
		GLint length;

		glGetProgramiv(
			program,
			GL_INFO_LOG_LENGTH,
			&length);

		auto infoLog = std::string(
			static_cast<size_t>(length),
			' ');

		glGetProgramInfoLog(
			program,
			length,
			&length,
			infoLog.data());

		return infoLog;
	}

	GLint GlGpuPipeline::getUniformLocation(
		GLuint program,
		const std::string& name)
	{
		auto location = glGetUniformLocation(
			program,
			name.c_str());

		if (location == -1)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Incorrect uniform name");
		}

		return location;
	}
	GLuint GlGpuPipeline::getUniformBlockIndex(
		GLuint program,
		const std::string& name)
	{
		auto index = glGetUniformBlockIndex(
			program,
			name.c_str());

		if (index == GL_INVALID_INDEX)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Incorrect uniform block name");
		}

		return index;
	}

	void GlGpuPipeline::setVertexAttributePointer(
		GLuint index,
		GLint size,
		GLenum type,
		GLboolean normalized,
		size_t stride,
		size_t offset) noexcept
	{
		glVertexAttribPointer(
			index,
			size,
			type,
			normalized,
			static_cast<GLsizei>(stride),
			reinterpret_cast<const GLvoid*>(offset));
	}

	void GlGpuPipeline::setUniform(
		GLint location, int32_t value) noexcept
	{
		glUniform1iv(location, 1, &value);
	}
	void GlGpuPipeline::setUniform(
		GLint location, uint32_t value) noexcept
	{
		glUniform1uiv(location, 1, &value);
	}
	void GlGpuPipeline::setUniform(
		GLint location, float value) noexcept
	{
		glUniform1fv(location, 1, &value);
	}
	void GlGpuPipeline::setUniform(
		GLint location, const IntVector2& value) noexcept
	{
		glUniform2iv(location, 1,
			reinterpret_cast<const GLint*>(&value));
	}
	void GlGpuPipeline::setUniform(
		GLint location, const IntVector3& value) noexcept
	{
		glUniform3iv(location, 1,
			reinterpret_cast<const GLint*>(&value));
	}
	void GlGpuPipeline::setUniform(
		GLint location, const IntVector4& value) noexcept
	{
		glUniform4iv(location, 1,
			reinterpret_cast<const GLint*>(&value));
	}
	void GlGpuPipeline::setUniform(
		GLint location, const Vector2& value) noexcept
	{
		glUniform2fv(location, 1,
			reinterpret_cast<const GLfloat*>(&value));
	}
	void GlGpuPipeline::setUniform(
		GLint location, const Vector3& value) noexcept
	{
		glUniform3fv(location, 1,
			reinterpret_cast<const GLfloat*>(&value));
	}
	void GlGpuPipeline::setUniform(
		GLint location, const Vector4& value) noexcept
	{
		glUniform4fv(location, 1,
			reinterpret_cast<const GLfloat*>(&value));
	}
	void GlGpuPipeline::setUniform(
		GLint location,
		const Matrix2& value,
		GLboolean transpose) noexcept
	{
		glUniformMatrix2fv(location, 1, transpose,
			reinterpret_cast<const GLfloat*>(&value));
	}
	void GlGpuPipeline::setUniform(
		GLint location,
		const Matrix3& value,
		GLboolean transpose) noexcept
	{
		glUniformMatrix3fv(location, 1, transpose,
			reinterpret_cast<const GLfloat*>(&value));
	}
	void GlGpuPipeline::setUniform(
		GLint location,
		const Matrix4& value,
		GLboolean transpose) noexcept
	{
		glUniformMatrix4fv(location, 1, transpose,
			reinterpret_cast<const GLfloat*>(&value));
	}

	GlGpuPipeline::GlGpuPipeline(
		GpuDrawMode drawMode) noexcept :
		GpuPipeline(drawMode),
		glDrawMode(toGlGpuDrawMode(drawMode))
	{
		program = glCreateProgram();
	}
	GlGpuPipeline::~GlGpuPipeline()
	{
		glDeleteProgram(program);
	}

	GLuint GlGpuPipeline::getProgram() const noexcept
	{
		return program;
	}
	GLenum GlGpuPipeline::getGlDrawMode() const noexcept
	{
		return glDrawMode;
	}

	void GlGpuPipeline::bind()
	{
		glUseProgram(program);
	}
	void GlGpuPipeline::unbind()
	{
		glUseProgram(GL_ZERO);
	}

	bool GlGpuPipeline::operator==(
		const GlGpuPipeline& pipeline) const noexcept
	{
		return program == pipeline.program;
	}
	bool GlGpuPipeline::operator!=(
		const GlGpuPipeline& pipeline) const noexcept
	{
		return program != pipeline.program;
	}

	bool GlGpuPipeline::less(
		const GlGpuPipeline& a,
		const GlGpuPipeline& b)
	{
		return a.program < b.program;
	}
}
