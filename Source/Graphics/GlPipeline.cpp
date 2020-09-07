#include "Injector/Graphics/GlPipeline.hpp"
#include "Injector/Graphics/GraphicsException.hpp"

namespace Injector
{
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
		throw GraphicsException("Not implemented OpenGL pipeline function");
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
			throw GraphicsException("Failed to get uniform location");

		return location;
	}
}
