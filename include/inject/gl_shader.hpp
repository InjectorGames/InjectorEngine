#pragma once
#include <inject/shader.hpp>

#include <GL/glew.h>
#include <SDL_opengl.h>
#include <SDL_rwops.h>

#include <vector>
#include <stdexcept>

namespace inject
{
	class GlShader : public Shader
	{
	protected:
		uint32_t shader;

		inline static uint32_t typeToEnum(const Type type)
		{
			switch (type)
			{
			default:
				throw std::runtime_error("Unsupported OpenGL shader type.");
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
			}
		}

		inline static uint32_t create(const Type type)
		{
			return static_cast<uint32_t>(glCreateShader(static_cast<GLenum>(typeToEnum(type))));
		}
		inline static void destroy(const uint32_t shader) noexcept
		{
			glDeleteShader(static_cast<GLuint>(shader));
		}

		inline static void setSource(const uint32_t shader, const char* source) noexcept
		{
			glShaderSource(static_cast<GLuint>(shader), GL_ONE, static_cast<const GLchar* const*>(&source), nullptr);
		}
		inline static void setSource(const uint32_t shader, const std::vector<const char*>& sources) noexcept
		{
			glShaderSource(static_cast<GLuint>(shader), static_cast<GLsizei>(sources.size()), static_cast<const GLchar* const*>(sources.data()), nullptr);
		}

		inline static void compile(const uint32_t shader) noexcept
		{
			glCompileShader(static_cast<GLuint>(shader));
		}
		inline static bool getCompileStatus(const uint32_t shader) noexcept
		{
			GLint success;
			glGetShaderiv(static_cast<GLuint>(shader), GL_COMPILE_STATUS, &success);
			return success == GL_TRUE;
		}
		inline static std::string getInfoLog(const uint32_t shader) noexcept
		{
			GLint length;
			glGetShaderiv(static_cast<GLuint>(shader), GL_INFO_LOG_LENGTH, &length);
			std::string infoLog(static_cast<size_t>(length), ' ');
			glGetShaderInfoLog(static_cast<GLuint>(shader), length, &length, static_cast<GLchar*>(infoLog.data()));
			return infoLog;
		}
	public:
		GlShader(const Type type, const std::vector<const char*>& sources) :
			Shader(type)
		{
			shader = create(type);
			setSource(shader, sources);
			compile(shader);

			if (!getCompileStatus(shader))
				throw std::runtime_error("Failed to compile OpenGL shader. " + getInfoLog(shader));
		}
		GlShader(const Type type, const std::string& string, const bool readFile) :
			Shader(type)
		{
			std::string sourceCode;

			if (readFile)
			{
				auto context = SDL_RWFromFile(string.c_str(), "rt");

				if (context == nullptr)
					throw std::runtime_error("Failed to open shader file. Error: " + std::string(SDL_GetError()));

				auto size = static_cast<int32_t>(SDL_RWsize(context));

				if (size < 0)
					throw ("Failed to get shader file size. Error: " + std::string(SDL_GetError()));

				sourceCode.resize(size, ' ');

				if(SDL_RWread(context, &sourceCode[0], sizeof(char), size) == 0)
					throw ("Failed to read shader from file. Error: " + std::string(SDL_GetError()));
			}
			else
			{
				sourceCode = string;
			}
				

			std::vector<const char*> sources;
			sources.push_back(sourceCode.c_str());

			// TODO: parse include

			shader = create(type);
			setSource(shader, sources);
			compile(shader);

			if (!getCompileStatus(shader))
			{
				auto infoLog = getInfoLog(shader);
				throw std::runtime_error("Failed to compile OpenGL shader. " + infoLog);
			}
		}
		virtual ~GlShader()
		{
			destroy(shader);
		}

		inline uint32_t getShader() const noexcept
		{
			return shader;
		}
	};
}
