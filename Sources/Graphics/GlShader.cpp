#include "Injector/Graphics/GlShader.hpp"
#include "Injector/Exception/Exception.hpp"

#include <vector>

namespace Injector
{
	const std::string GlShader::glHeader = "#version 330 core\n\n#define highp \n#define mediump \n#define lowp \n";
	const std::string GlShader::glesHeader = "#version 300 es\n";

	GlShader::GlShader(
		GLenum stage,
		const std::string& source,
		bool _gles) :
		gles(_gles)
	{
		auto sources = std::vector<const char*>();

		if (_gles)
			sources.push_back(glesHeader.c_str());
		else
			sources.push_back(glHeader.c_str());

		sources.push_back(source.c_str());

		shader = glCreateShader(stage);

		glShaderSource(shader, 
			static_cast<GLsizei>(sources.size()), 
			static_cast<const GLchar* const*>(sources.data()),
			nullptr);

		glCompileShader(shader);

		if (!getCompileStatus(shader))
		{
			auto log = getInfoLog(shader);
			glDeleteShader(shader);

			throw Exception("GlShader", "GlShader", 
				"Failed to compile shader: " + log);
		}
	}
	GlShader::~GlShader()
	{
		glDeleteShader(shader);
	}

	bool GlShader::isGLES() const noexcept
	{
		return gles;
	}
	uint32_t GlShader::getShader() const noexcept
	{
		return shader;
	}

	bool GlShader::getCompileStatus(GLuint shader) noexcept
	{
		GLint success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		return success == GL_TRUE;
	}
	std::string GlShader::getInfoLog(GLuint shader) noexcept
	{
		GLint length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		std::string infoLog(static_cast<size_t>(length), ' ');
		glGetShaderInfoLog(shader, length, &length, infoLog.data());
		return infoLog;
	}
}
