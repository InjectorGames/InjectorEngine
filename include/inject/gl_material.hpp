#pragma once
#include <inject/gl_shader.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace inject
{
	class GlMaterial
	{
	protected:
		uint32_t program;

		inline static uint32_t create() noexcept
		{
			return static_cast<uint32_t>(glCreateProgram());
		}
		inline static void destroy(const uint32_t program) noexcept
		{
			glDeleteProgram(static_cast<GLuint>(program));
		}
		inline static void use(const uint32_t program) noexcept
		{
			glUseProgram(static_cast<GLuint>(program));
		}

		inline static void attach(const uint32_t program, const uint32_t shader) noexcept
		{
			glAttachShader(static_cast<GLuint>(program), static_cast<GLuint>(shader));
		}
		inline static void detach(const uint32_t program, const uint32_t shader) noexcept
		{
			glDetachShader(static_cast<GLuint>(program), static_cast<GLuint>(shader));
		}

		inline static void link(const uint32_t program) noexcept
		{
			glLinkProgram(static_cast<GLuint>(program));
		}
		inline static bool getLinkStatus(const uint32_t program) noexcept
		{
			GLint success;
			glGetProgramiv(static_cast<GLuint>(program), GL_LINK_STATUS, &success);
			return success == GL_TRUE;
		}
		inline static std::string getInfoLog(const uint32_t program) noexcept
		{
			GLint length;
			glGetProgramiv(static_cast<GLuint>(program), GL_INFO_LOG_LENGTH, &length);
			std::string infoLog(static_cast<size_t>(length), ' ');
			glGetProgramInfoLog(static_cast<GLuint>(program), length, &length, static_cast<GLchar*>(infoLog.data()));
			return infoLog;
		}

		inline static int32_t getUniformLocation(const uint32_t program, const std::string& name)
		{
			auto location = static_cast<GLint>(glGetUniformLocation(static_cast<GLuint>(program), static_cast<const GLchar*>(name.c_str())));
			if (location == -1)
				throw std::runtime_error("Failed to get uniform location");
			return location;
		}

		static void setUniform(const int32_t index, const int32_t value) noexcept
		{
			glUniform1i(static_cast<GLint>(index), static_cast<GLint>(value));
		}
		static void setUniform(const int32_t index, const float value) noexcept
		{
			glUniform1f(static_cast<GLint>(index), static_cast<GLfloat>(value));
		}
		static void setUniform(const int32_t index, const glm::vec2& value) noexcept
		{
			glUniform2fv(static_cast<GLint>(index), GL_ONE, static_cast<const GLfloat*>(glm::value_ptr(value)));
		}
		static void setUniform(const int32_t index, const glm::vec3& value) noexcept
		{
			glUniform3fv(static_cast<GLint>(index), GL_ONE, static_cast<const GLfloat*>(glm::value_ptr(value)));
		}
		static void setUniform(const int32_t index, const glm::vec4& value) noexcept
		{
			glUniform4fv(static_cast<GLint>(index), GL_ONE, static_cast<const GLfloat*>(glm::value_ptr(value)));
		}
		static void setUniform(const int32_t index, const glm::mat2& value) noexcept
		{
			glUniformMatrix2fv(static_cast<GLint>(index), GL_ONE, GL_FALSE, static_cast<const GLfloat*>(glm::value_ptr(value)));
		}
		static void setUniform(const int32_t index, const glm::mat3& value) noexcept
		{
			glUniformMatrix3fv(static_cast<GLint>(index), GL_ONE, GL_FALSE, static_cast<const GLfloat*>(glm::value_ptr(value)));
		}
		static void setUniform(const int32_t index, const glm::mat4& value) noexcept
		{
			glUniformMatrix4fv(static_cast<GLint>(index), GL_ONE, GL_FALSE, static_cast<const GLfloat*>(glm::value_ptr(value)));
		}
	public:
		GlMaterial(const std::shared_ptr<GlShader>& shader)
		{
			program = create();
			attach(program, shader->getShader());
			link(program);
			detach(program, shader->getShader());

			if (!getLinkStatus(program))
			{
				auto infoLog = getInfoLog(program);
				throw std::runtime_error("Failed to link OpenGL program. " + infoLog);
			}
		}
		GlMaterial(const std::shared_ptr<GlShader>& shader1,
			const std::shared_ptr<GlShader>& shader2)
		{
			program = create();
			attach(program, shader1->getShader());
			attach(program, shader2->getShader());
			link(program);
			detach(program, shader2->getShader());
			detach(program, shader1->getShader());

			if (!getLinkStatus(program))
			{
				auto infoLog = getInfoLog(program);
				throw std::runtime_error("Failed to link OpenGL program. " + infoLog);
			}
		}
		GlMaterial(const std::shared_ptr<GlShader>& shader1,
			const std::shared_ptr<GlShader>& shader2,
			const std::shared_ptr<GlShader>& shader3)
		{
			program = create();
			attach(program, shader1->getShader());
			attach(program, shader2->getShader());
			attach(program, shader3->getShader());
			link(program);
			detach(program, shader3->getShader());
			detach(program, shader2->getShader());
			detach(program, shader1->getShader());

			if (!getLinkStatus(program))
			{
				auto infoLog = getInfoLog(program);
				throw std::runtime_error("Failed to link OpenGL program. " + infoLog);
			}
		}
		GlMaterial(const std::shared_ptr<GlShader>& shader1,
			const std::shared_ptr<GlShader>& shader2,
			const std::shared_ptr<GlShader>& shader3,
			const std::shared_ptr<GlShader>& shader4)
		{
			program = create();
			attach(program, shader1->getShader());
			attach(program, shader2->getShader());
			attach(program, shader3->getShader());
			attach(program, shader4->getShader());
			link(program);
			detach(program, shader4->getShader());
			detach(program, shader3->getShader());
			detach(program, shader2->getShader());
			detach(program, shader1->getShader());

			if (!getLinkStatus(program))
			{
				auto infoLog = getInfoLog(program);
				throw std::runtime_error("Failed to link OpenGL program. " + infoLog);
			}
		}
		virtual ~GlMaterial()
		{
			destroy(program);
		}

		inline uint32_t getProgram() const noexcept
		{
			return program;
		}
		inline int32_t getUniformLocation(const std::string& name) const
		{
			return getUniformLocation(program, name);
		}

		virtual void use() const
		{
			use(program);
		}
		virtual void unuse() const
		{
			use(0);
		}

		virtual void setModel(const glm::mat4& value) const
		{}
		virtual void setView(const glm::mat4& value) const
		{}
		virtual void setProj(const glm::mat4& value) const
		{}
		virtual void setViewProj(const glm::mat4& value) const
		{}
		virtual void setMVP(const glm::mat4& value) const
		{}
	};
}
