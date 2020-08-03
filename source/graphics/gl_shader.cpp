#include <injector/graphics/gl_shader.hpp>
#include <injector/file_stream.hpp>

#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	const std::string GlShader::glHeader = "#version 300 es\n";
	const std::string GlShader::glesHeader = "#version 330 core\n\n#define highp \n#define mediump \n#define lowp \n";

	uint32_t GlShader::stageToEnum(ShaderStage stage)
	{
		switch (stage)
		{
		case ShaderStage::Vertex:
			return GL_VERTEX_SHADER;
		case ShaderStage::TessellationControl:
			return GL_TESS_CONTROL_SHADER;
		case ShaderStage::TessellationEvaluation:
			return GL_TESS_EVALUATION_SHADER;
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

	uint32_t GlShader::create(ShaderStage stage)
	{
		auto type = static_cast<GLenum>(stageToEnum(stage));
		return static_cast<uint32_t>(glCreateShader(type));
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

	GlShader::GlShader(ShaderStage stage, const std::vector<const char*>& sources) :
		Shader(stage)
	{
		instance = create(stage);
		setSource(instance, sources);
		compile(instance);

		if (!getCompileStatus(instance))
		{
			destroy(instance);
			throw std::runtime_error("Failed to compile OpenGL shader: " + getInfoLog(instance));
		}
	}
	GlShader::GlShader(bool _gles, ShaderStage stage, const std::string& path) :
		Shader(stage),
		gles(_gles)
	{
		std::string extension;

		switch (stage)
		{
		case ShaderStage::Vertex:
			extension = ".vert";
			break;
		case ShaderStage::TessellationControl:
			extension = ".tesc";
			break;
		case ShaderStage::TessellationEvaluation:
			extension = ".tese";
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

		instance = create(stage);
		setSource(instance, sources);
		compile(instance);

		if (!getCompileStatus(instance))
		{
			destroy(instance);
			throw std::runtime_error("Failed to compile OpenGL shader. " + getInfoLog(instance));
		}
	}
	GlShader::~GlShader()
	{
		destroy(instance);
	}

	bool GlShader::getGLES() const noexcept
	{
		return gles;
	}
	uint32_t GlShader::getInstance() const noexcept
	{
		return instance;
	}
}
