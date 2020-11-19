#include "Injector/Graphics/OpenGL/GlGpuShader.hpp"
#include "Injector/Exception/NullException.hpp"
#include "Injector/Graphics/OpenGL/GlGpuShaderStage.hpp"

#include <vector>

namespace Injector
{
	bool GlGpuShader::getCompileStatus(GLuint shader)
	{
		GLint success;

		glGetShaderiv(
			shader,
			GL_COMPILE_STATUS,
			&success);

		return success == GL_TRUE;
	}
	std::string GlGpuShader::getInfoLog(GLuint shader)
	{
		GLint length;

		glGetShaderiv(
			shader,
			GL_INFO_LOG_LENGTH,
			&length);

		auto infoLog = std::string(
			static_cast<size_t>(length),
			' ');

		glGetShaderInfoLog(
			shader,
			length,
			&length,
			infoLog.data());

		return infoLog;
	}

	const std::string GlGpuShader::glHeader =
		"#version 330 core\n\n#define highp \n#define mediump \n#define lowp \n";
	const std::string GlGpuShader::glesHeader =
		"#version 300 es\n";

	GlGpuShader::GlGpuShader(bool _gles,
		GpuShaderStage stage,
		const std::shared_ptr<ShaderData>& data) :
		GpuShader(stage),
		gles(_gles)
	{
		if (!data)
		{
			throw NullException(
				THIS_FUNCTION_NAME,
				"data");
		}

		glStage = toGlGpuShaderStage(stage);
		shader = glCreateShader(glStage);

		const char* sources[2];

		if (_gles)
			sources[0] = glesHeader.c_str();
		else
			sources[0] = glHeader.c_str();

		sources[1] = reinterpret_cast<const char*>(
			data->code.data());

		glShaderSource(
			shader,
			2,
			sources,
			nullptr);

		glCompileShader(shader);

		if (!getCompileStatus(shader))
		{
			auto log = getInfoLog(shader);
			glDeleteShader(shader);

			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to compile shader: " + log);
		}
	}
	GlGpuShader::~GlGpuShader()
	{
		glDeleteShader(shader);
	}

	bool GlGpuShader::isGLES() const noexcept
	{
		return gles;
	}
	GLuint GlGpuShader::getShader() const noexcept
	{
		return shader;
	}
	GLuint GlGpuShader::getGlStage() const noexcept
	{
		return glStage;
	}
}
