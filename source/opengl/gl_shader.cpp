#include <injector_engine.hpp>

namespace Injector
{
	GLenum GlShader::TypeToEnum(Type type)
	{
		switch (type)
		{
		default:
			throw std::runtime_error("Unsupported shader type for OpenGL.");
		case Injector::Shader::Type::Vertex:
			return GL_VERTEX_SHADER;
		case Injector::Shader::Type::TessellationControl:
			return GL_TESS_CONTROL_SHADER;
		case Injector::Shader::Type::TessellationEvaluation:
			return GL_TESS_EVALUATION_SHADER;
		case Injector::Shader::Type::Geometry:
			return GL_GEOMETRY_SHADER;
		case Injector::Shader::Type::Fragment:
			return GL_FRAGMENT_SHADER;
		case Injector::Shader::Type::Compute:
			return GL_COMPUTE_SHADER;
		}
	}
	void GlShader::SetSource(GLuint shader, const std::vector<const GLchar*>& source)
	{
		glShaderSource(shader, static_cast<GLsizei>(source.size()), source.data(), nullptr);
	}
	GLint GlShader::GetCompileStatus(GLuint shader)
	{
		GLint success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		return success;
	}
	std::string GlShader::GetInfoLog(GLuint shader)
	{
		GLint length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		std::string buffer(length, ' ');
		glGetShaderInfoLog(shader, length, &length, &buffer[0]);
		return buffer;
	}

	GlShader::GlShader(const std::string& filePath, Type type) : Shader(type)
	{
		auto shaderSource = Engine::ReadTextFromFile(filePath);
		shaderSource.insert(0, "#define highp\n#define mediump\n#define lowp\n");

		instance = glCreateShader(TypeToEnum(type));

		std::vector<const GLchar*> source;
		SetSource(instance, source);

		glCompileShader(instance);

		if (GetCompileStatus(instance) == GL_FALSE)
			throw std::runtime_error("Failed to compile OpenGL shader. " + GetInfoLog(instance));
	}
	GlShader::~GlShader()
	{
		glDeleteShader(instance);
		instance = GL_ZERO;
	}

	bool GlShader::operator==(GlShader const& s) const noexcept
	{
		return instance == s.instance;
	}

	bool GlShader::operator!=(GlShader const& s) const noexcept
	{
		return instance != s.instance;
	}

	bool GlShader::operator<(GlShader const& s) const noexcept
	{
		return instance < s.instance;
	}
}
