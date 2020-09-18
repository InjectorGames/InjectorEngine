#include "Injector/Graphics/GlGpuShader.hpp"
#include "Injector/Exception/NullException.hpp"

#include <vector>

namespace Injector
{
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
			throw NullException("GlGpuShader", "GlGpuShader", "data");

		glStage = toGlStage(stage);
		shader = glCreateShader(glStage);

		auto sources = std::vector<const char*>();

		if (_gles)
			sources.push_back(glesHeader.c_str());
		else
			sources.push_back(glHeader.c_str());

		sources.push_back(reinterpret_cast<const char*>(
			data->code.data()));

		glShaderSource(shader, 
			static_cast<GLsizei>(sources.size()), 
			static_cast<const GLchar* const*>(sources.data()),
			nullptr);

		glCompileShader(shader);

		if (!getCompileStatus(shader))
		{
			auto log = getInfoLog(shader);
			glDeleteShader(shader);

			throw Exception("GlGpuShader", "GlGpuShader", 
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

	GLenum GlGpuShader::toGlStage(GpuShaderStage stage)
	{
		switch (stage)
		{
		case GpuShaderStage::Vertex:
			return GL_VERTEX_SHADER;
		case GpuShaderStage::Geometry:
			return GL_GEOMETRY_SHADER;
		case GpuShaderStage::Fragment:
			return GL_FRAGMENT_SHADER;
		case GpuShaderStage::Compute:
			return GL_COMPUTE_SHADER;
		default:
			throw Exception("GlGpuShader", "toGlStage", "Usupported stage");
		}
	}
	bool GlGpuShader::getCompileStatus(GLuint shader)
	{
		GLint success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		return success == GL_TRUE;
	}
	std::string GlGpuShader::getInfoLog(GLuint shader)
	{
		GLint length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		std::string infoLog(static_cast<size_t>(length), ' ');
		glGetShaderInfoLog(shader, length, &length, infoLog.data());
		return infoLog;
	}
}
