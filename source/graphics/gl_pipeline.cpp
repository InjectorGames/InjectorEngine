#include <injector/graphics/gl_pipeline.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	/*
	void GlMaterial::setUniform(int32_t index, int value) noexcept
	{
		glUniform1i(static_cast<GLint>(index), static_cast<GLint>(value));
	}
	void GlMaterial::setUniform(int32_t index, float value) noexcept
	{
		glUniform1f(static_cast<GLint>(index), static_cast<GLfloat>(value));
	}
	void GlMaterial::setUniform(int32_t index, const Vector2& vector) noexcept
	{
		glUniform2fv(static_cast<GLint>(index), GL_ONE,
			reinterpret_cast<const GLfloat*>(&vector));
	}
	void GlMaterial::setUniform(int32_t index, const Vector3& vector) noexcept
	{
		glUniform3fv(static_cast<GLint>(index), GL_ONE, 
			reinterpret_cast<const GLfloat*>(&vector));
	}
	void GlMaterial::setUniform(int32_t index, const Vector4& vector) noexcept
	{
		glUniform4fv(static_cast<GLint>(index), GL_ONE,
			reinterpret_cast<const GLfloat*>(&vector));
	}
	void GlMaterial::setUniform(int32_t index, const Matrix2& matrix) noexcept
	{
		glUniformMatrix2fv(static_cast<GLint>(index), GL_ONE, GL_FALSE,
			reinterpret_cast<const GLfloat*>(&matrix));
	}
	void GlMaterial::setUniform(int32_t index, const Matrix3& matrix) noexcept
	{
		glUniformMatrix3fv(static_cast<GLint>(index), GL_ONE, GL_FALSE,
			reinterpret_cast<const GLfloat*>(&matrix));
	}
	void GlMaterial::setUniform(int32_t index, const Matrix4& matrix) noexcept
	{
		glUniformMatrix4fv(static_cast<GLint>(index), GL_ONE, GL_FALSE,
			reinterpret_cast<const GLfloat*>(&matrix));
	}

	void GlMaterial::enableDepthTest() noexcept
	{
		glEnable(GL_DEPTH_TEST);
	}
	void GlMaterial::disableDepthTest() noexcept
	{
		glDisable(GL_DEPTH_TEST);
	}
	void GlMaterial::setDepthTestFunction(uint32_t function) noexcept
	{
		glDepthFunc(static_cast<GLenum>(function));
	}

	void GlMaterial::enableBlend() noexcept
	{
		glEnable(GL_BLEND);
	}
	void GlMaterial::disableBlend() noexcept
	{
		glDisable(GL_BLEND);
	}
	void GlMaterial::setBlendFunction(uint32_t source, uint32_t destination) noexcept
	{
		glBlendFunc(static_cast<GLenum>(source), static_cast<GLenum>(destination));
	}
	void GlMaterial::setBlendFunction(uint32_t sourceRgb, uint32_t destinationRgb,
		uint32_t sourceAlpha, uint32_t destinationAlpha) noexcept
	{
		glBlendFuncSeparate(static_cast<GLenum>(sourceRgb), static_cast<GLenum>(destinationRgb),
			static_cast<GLenum>(sourceAlpha), static_cast<GLenum>(destinationAlpha));
	}

	int32_t GlMaterial::getUniformLocation(const std::string& name)
	{
		return getUniformLocation(instance, name);
	}*/

	GlPipeline::GlPipeline(
		GLenum _drawMode,
		const std::vector<GlVertexAttribute>& _vertexAttributes) : 
		drawMode(_drawMode),
		vertexAttributes(_vertexAttributes)
	{
		program = glCreateProgram();
	}
	GlPipeline::~GlPipeline()
	{
		glDeleteProgram(program);
	}

	GLuint GlPipeline::getProgram() const noexcept
	{
		return program;
	}
	GLenum GlPipeline::getDrawMode() const noexcept
	{
		return drawMode;
	}
	const std::vector<GlVertexAttribute>& GlPipeline::getVertexAttributes() const noexcept
	{
		return vertexAttributes;
	}

	void GlPipeline::flush()
	{
		throw std::runtime_error("Not implemented OpenGL pipeline function");
	}
	void GlPipeline::bind()
	{
		glUseProgram(program);
	}

	bool GlPipeline::getLinkStatus(GLuint program) noexcept
	{
		GLint success;
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		return success == GL_TRUE;
	}
	std::string GlPipeline::getInfoLog(GLuint program) noexcept
	{
		GLint length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		std::string infoLog(length, ' ');
		glGetProgramInfoLog(program, length, &length, infoLog.data());
		return infoLog;
	}
	GLint GlPipeline::getUniformLocation(GLuint program, const std::string& name)
	{
		auto location = glGetUniformLocation(program, name.c_str());

		if (location == -1)
			throw std::runtime_error("Failed to get uniform location");

		return location;
	}
}
