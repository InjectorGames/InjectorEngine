#include <injector_engine/opengl.hpp>

namespace InjectorEngine
{
	gl::GLenum GlShader::TypeToEnum(ShaderType type)
	{
		switch (type)
		{
		default:
			throw std::runtime_error("Unsupported OpenGL shader type.");
		case InjectorEngine::ShaderType::Vertex:
			return gl::GL_VERTEX_SHADER;
		case InjectorEngine::ShaderType::TessellationControl:
			return gl::GL_TESS_CONTROL_SHADER;
		case InjectorEngine::ShaderType::TessellationEvaluation:
			return gl::GL_TESS_EVALUATION_SHADER;
		case InjectorEngine::ShaderType::Geometry:
			return gl::GL_GEOMETRY_SHADER;
		case InjectorEngine::ShaderType::Fragment:
			return gl::GL_FRAGMENT_SHADER;
		case InjectorEngine::ShaderType::Compute:
			return gl::GL_COMPUTE_SHADER;
		}
	}

	gl::GLuint GlShader::Create(ShaderType type)
	{
		return gl::glCreateShader(TypeToEnum(type));
	}
	void GlShader::Delete(gl::GLuint shader)
	{
		gl::glDeleteShader(shader);
	}

	void GlShader::SetSource(gl::GLuint shader, const char* source)
	{
		gl::glShaderSource(shader, 1, &source, nullptr);
	}
	void GlShader::SetSource(gl::GLuint shader, const std::vector<const char*>& sources)
	{
		gl::glShaderSource(shader, static_cast<gl::GLsizei>(sources.size()), sources.data(), nullptr);
	}

	void GlShader::Compile(gl::GLuint shader)
	{
		gl::glCompileShader(shader);
	}
	bool GlShader::GetCompileStatus(gl::GLuint shader)
	{
		gl::GLint success;
		gl::glGetShaderiv(shader, gl::GL_COMPILE_STATUS, &success);
		return success;
	}
	std::string GlShader::GetInfoLog(gl::GLuint shader)
	{
		gl::GLint length;
		gl::glGetShaderiv(shader, gl::GL_INFO_LOG_LENGTH, &length);
		std::string infoLog(length, ' ');
		gl::glGetShaderInfoLog(shader, length, &length, &infoLog[0]);
		return infoLog;
	}

	GlShader::GlShader(ShaderType type, const std::vector<const char*>& sources) :
		Shader(type), shader(Create(type))
	{
		SetSource(shader, sources);
		Compile(shader);

		if (!GetCompileStatus(shader))
			throw std::runtime_error("Failed to compile OpenGL shader. " + GetInfoLog(shader));
	}
	GlShader::GlShader(ShaderType type, const std::string& string, bool readFile) :
		Shader(type), shader(Create(type))
	{
		std::string sourceCode;

		if (readFile)
			sourceCode = Engine::ReadTextFromFile(string);
		else
			sourceCode = string;

		std::vector<const char*> sources;
		sources.push_back(sourceCode.c_str());

		// TODO: parse include

		SetSource(shader, sources);
		Compile(shader);

		if (!GetCompileStatus(shader))
		{
			auto infoLog = GetInfoLog(shader);
			throw std::runtime_error("Failed to compile OpenGL shader. " + infoLog);
		}	
	}

	GlShader::~GlShader()
	{
		Delete(shader);
	}
}
