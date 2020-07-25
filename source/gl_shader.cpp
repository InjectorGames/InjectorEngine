#include <injector/gl_shader.hpp>
#include <injector/file_stream.hpp>

#include <stdexcept>

#include <GL/glew.h>
#include <SDL_opengl.h>

namespace INJECTOR_NAMESPACE
{
	uint32_t GlShader::typeToEnum(Type type)
	{
		switch (type)
		{
		case Type::Vertex:
			return GL_VERTEX_SHADER;
		case Type::TessellationControl:
			return GL_TESS_CONTROL_SHADER;
		case Type::TessellationEvaluation:
			return GL_TESS_EVALUATION_SHADER;
		case Type::Geometry:
			return GL_GEOMETRY_SHADER;
		case Type::Fragment:
			return GL_FRAGMENT_SHADER;
		case Type::Compute:
			return GL_COMPUTE_SHADER;
		default:
			throw std::runtime_error("Unsupported OpenGL shader type");
		}
	}

	uint32_t GlShader::create(Type type) noexcept
	{
		return static_cast<uint32_t>(glCreateShader(static_cast<GLenum>(typeToEnum(type))));
	}
	void GlShader::destroy(uint32_t shader) noexcept
	{
		glDeleteShader(static_cast<GLuint>(shader));
	}

	void GlShader::setSource(uint32_t shader, const char* source) noexcept
	{
		glShaderSource(static_cast<GLuint>(shader), GL_ONE,
			static_cast<const GLchar* const*>(&source), nullptr);
	}
	void GlShader::setSource(uint32_t shader,
		const std::vector<const char*>& sources) noexcept
	{
		glShaderSource(static_cast<GLuint>(shader), static_cast<GLsizei>(sources.size()), static_cast<const GLchar* const*>(sources.data()), nullptr);
	}

	void GlShader::compile(uint32_t shader) noexcept
	{
		glCompileShader(static_cast<GLuint>(shader));
	}
	bool GlShader::getCompileStatus(uint32_t shader) noexcept
	{
		GLint success;
		glGetShaderiv(static_cast<GLuint>(shader), GL_COMPILE_STATUS, &success);
		return success == GL_TRUE;
	}
	std::string GlShader::getInfoLog(uint32_t shader) noexcept
	{
		GLint length;
		glGetShaderiv(static_cast<GLuint>(shader), GL_INFO_LOG_LENGTH, &length);
		std::string infoLog(static_cast<size_t>(length), ' ');
		glGetShaderInfoLog(static_cast<GLuint>(shader), length, &length, static_cast<GLchar*>(infoLog.data()));
		return infoLog;
	}

	GlShader::GlShader(Type type, const std::vector<const char*>& sources) :
		Shader(type)
	{
		instance = create(type);
		setSource(instance, sources);
		compile(instance);

		if (!getCompileStatus(instance))
			throw std::runtime_error("Failed to compile OpenGL shader: " +
				getInfoLog(instance));
	}
	GlShader::GlShader(Type type, const std::string& string, bool readFile) :
		Shader(type)
	{
		std::string sourceCode;

		if (readFile)
		{
			auto fileStream = FileStream(string, std::ios::in | std::ios::ate);

			if (!fileStream.is_open())
				throw std::runtime_error("Failed to open shader file");

			auto size = static_cast<size_t>(fileStream.tellg());
			fileStream.seekg(0, fileStream.beg);
			sourceCode.resize(size, ' ');
			fileStream.read(sourceCode.data(), size);
		}
		else
		{
			sourceCode = string;
		}

		std::vector<const char*> sources;
		sources.push_back(sourceCode.c_str());

		// TODO: parse include

		instance = create(type);
		setSource(instance, sources);
		compile(instance);

		if (!getCompileStatus(instance))
		{
			auto infoLog = getInfoLog(instance);
			throw std::runtime_error("Failed to compile OpenGL shader. " + infoLog);
		}
	}
	GlShader::~GlShader()
	{
		destroy(instance);
	}

	uint32_t GlShader::getInstance() const noexcept
	{
		return instance;
	}
}
