#include <injector/graphics/gl_shader.hpp>
#include <injector/file_stream.hpp>

#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	const std::string GlShader::glHeader = "#version 300 es\n";
	const std::string GlShader::glesHeader = "#version 330 core\n\n#define highp \n#define mediump \n#define lowp \n";

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
		glGetShaderInfoLog(shader, length, &length, static_cast<GLchar*>(infoLog.data()));
		return infoLog;
	}

	GlShader::GlShader(
		bool _gles,
		const std::string& path,
		ShaderStage stage) :
		Shader(stage),
		gles(_gles)
	{
		std::string extension;

		switch (stage)
		{
		case ShaderStage::Vertex:
			extension = ".vert";
			break;
		case ShaderStage::Geometry:
			extension = ".geom";
			break;
		case ShaderStage::Fragment:
			extension = ".frag";
			break;
		case ShaderStage::Compute:
			extension = ".comp";
			break;
		default:
			throw std::runtime_error("Unsupported OpenGL shader stage");
		}

		auto fileStream = FileStream(path + extension, std::ios::in | std::ios::ate);

		if (!fileStream.is_open())
			throw std::runtime_error("Failed to open shader file: " + path + extension);

		auto size = static_cast<size_t>(fileStream.tellg());
		fileStream.seekg(0, fileStream.beg);

		auto source = std::string(size, ' ');
		fileStream.read(source.data(), size);

		auto sources = std::vector<const char*>();

		if (_gles)
			sources.push_back(glesHeader.c_str());
		else
			sources.push_back(glHeader.c_str());

		sources.push_back(source.c_str());

		shader = glCreateShader(toGlStage(stage));
		glShaderSource(shader, static_cast<GLsizei>(sources.size()), 
			static_cast<const GLchar* const*>(sources.data()), nullptr);
		glCompileShader(shader);

		if (!getCompileStatus(shader))
		{
			glDeleteShader(shader);
			throw std::runtime_error("Failed to compile OpenGL shader. " +
				getInfoLog(shader));
		}
	}
	GlShader::~GlShader()
	{
		glDeleteShader(shader);
	}

	bool GlShader::getGLES() const noexcept
	{
		return gles;
	}
	uint32_t GlShader::getShader() const noexcept
	{
		return shader;
	}

	GLenum GlShader::toGlStage(ShaderStage stage)
	{
		switch (stage)
		{
		case ShaderStage::Vertex:
			return GL_VERTEX_SHADER;
		case ShaderStage::Geometry:
			return GL_GEOMETRY_SHADER;
		case ShaderStage::Fragment:
			return GL_FRAGMENT_SHADER;
		case ShaderStage::Compute:
			return GL_COMPUTE_SHADER;
		default:
			throw std::runtime_error("Unsupported OpenGL shader stage");
		}
	}
	ShaderStage GlShader::toStage(GLenum stage)
	{
		switch (stage)
		{
		case GL_VERTEX_SHADER:
			return ShaderStage::Vertex;
		case GL_GEOMETRY_SHADER:
			return ShaderStage::Geometry;
		case GL_FRAGMENT_SHADER:
			return ShaderStage::Fragment;
		case GL_COMPUTE_SHADER:
			return ShaderStage::Compute;
		default:
			throw std::runtime_error("Unsupported OpenGL shader stage");
		}
	}
}
