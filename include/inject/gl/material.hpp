#pragma once
#include <inject/glm_defines.hpp>
#include <inject/gl/shader.hpp>

namespace INJECT_NAMESPACE
{
	class GlMaterial
	{
	public:
		enum class DepthTestType : GLenum
		{
			// Never passes
			Never = GL_NEVER,
			// Passes if the incoming depth value is less than the stored depth value
			Less = GL_LESS,
			// Passes if the incoming depth value is equal to the stored depth value
			Equal = GL_EQUAL,
			// Passes if the incoming depth value is less than or equal to the stored depth value
			LessEqual = GL_LEQUAL,
			// Passes if the incoming depth value is greater than the stored depth value
			Greater = GL_GREATER,
			// Passes if the incoming depth value is not equal to the stored depth value
			NotEqual = GL_NOTEQUAL,
			// Passes if the incoming depth value is greater than or equal to the stored depth value
			GreaterEqual = GL_GEQUAL,
			// Always passes
			Always = GL_ALWAYS,
		};
		enum class BlendType : GLenum
		{
			Zero = GL_ZERO,
			One = GL_ONE,
			SrcColor = GL_SRC_COLOR,
			OneMinusSrcColor = GL_ONE_MINUS_SRC_COLOR,
			DstColor = GL_DST_COLOR,
			OneMinusDstColor = GL_ONE_MINUS_DST_COLOR,
			SrcAlpha = GL_SRC_ALPHA,
			OneMinusSrcAlpha = GL_ONE_MINUS_SRC_ALPHA,
			DstAlpha = GL_DST_ALPHA,
			OneMinusDstAlpha = GL_ONE_MINUS_DST_ALPHA,
			ConstantColor = GL_CONSTANT_COLOR,
			OneMinusConstantColor = GL_ONE_MINUS_CONSTANT_COLOR,
			ConstantAlpha = GL_CONSTANT_ALPHA,
			OneMinusConstantAlpha = GL_ONE_MINUS_CONSTANT_ALPHA,
			SrcAlphaSaturate = GL_SRC_ALPHA_SATURATE,
			Src1Color = GL_SRC1_COLOR,
			OneMinusSrc1Color = GL_ONE_MINUS_SRC1_COLOR,
			Src1Alpha = GL_SRC1_ALPHA,
			OneMinusSrc1Alpha = GL_ONE_MINUS_SRC1_ALPHA,
		};
	protected:
		uint32_t program;

		inline static const uint32_t create() noexcept
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
		inline static const bool getLinkStatus(const uint32_t program) noexcept
		{
			GLint success;
			glGetProgramiv(static_cast<GLuint>(program), GL_LINK_STATUS, &success);
			return success == GL_TRUE;
		}
		inline static const std::string getInfoLog(const uint32_t program) noexcept
		{
			GLint length;
			glGetProgramiv(static_cast<GLuint>(program), GL_INFO_LOG_LENGTH, &length);
			std::string infoLog(static_cast<size_t>(length), ' ');
			glGetProgramInfoLog(static_cast<GLuint>(program), length, &length, static_cast<GLchar*>(infoLog.data()));
			return infoLog;
		}

		inline static const int32_t getUniformLocation(const uint32_t program, const std::string& name)
		{
			auto location = static_cast<GLint>(glGetUniformLocation(static_cast<GLuint>(program), static_cast<const GLchar*>(name.c_str())));
			if (location == -1)
				throw std::runtime_error("Failed to get uniform location");
			return location;
		}

		inline static void setUniform(const int32_t index, const int32_t value) noexcept
		{
			glUniform1i(static_cast<GLint>(index), static_cast<GLint>(value));
		}
		inline static void setUniform(const int32_t index, const float value) noexcept
		{
			glUniform1f(static_cast<GLint>(index), static_cast<GLfloat>(value));
		}
		inline static void setUniform(const int32_t index, const glm::vec2& value) noexcept
		{
			glUniform2fv(static_cast<GLint>(index), GL_ONE, static_cast<const GLfloat*>(glm::value_ptr(value)));
		}
		inline static void setUniform(const int32_t index, const glm::vec3& value) noexcept
		{
			glUniform3fv(static_cast<GLint>(index), GL_ONE, static_cast<const GLfloat*>(glm::value_ptr(value)));
		}
		inline static void setUniform(const int32_t index, const glm::vec4& value) noexcept
		{
			glUniform4fv(static_cast<GLint>(index), GL_ONE, static_cast<const GLfloat*>(glm::value_ptr(value)));
		}
		inline static void setUniform(const int32_t index, const glm::mat2& value) noexcept
		{
			glUniformMatrix2fv(static_cast<GLint>(index), GL_ONE, GL_FALSE, static_cast<const GLfloat*>(glm::value_ptr(value)));
		}
		inline static void setUniform(const int32_t index, const glm::mat3& value) noexcept
		{
			glUniformMatrix3fv(static_cast<GLint>(index), GL_ONE, GL_FALSE, static_cast<const GLfloat*>(glm::value_ptr(value)));
		}
		inline static void setUniform(const int32_t index, const glm::mat4& value) noexcept
		{
			glUniformMatrix4fv(static_cast<GLint>(index), GL_ONE, GL_FALSE, static_cast<const GLfloat*>(glm::value_ptr(value)));
		}

		inline static void enableDepthTest() noexcept
		{
			glEnable(GL_DEPTH_TEST);
		}
		inline static void disableDepthTest() noexcept
		{
			glDisable(GL_DEPTH_TEST);
		}
		inline static void setDepthTestFunction(const DepthTestType function) noexcept
		{
			glDepthFunc(static_cast<GLenum>(function));
		}

		inline static void enableBlend() noexcept
		{
			glEnable(GL_BLEND);
		}
		inline static void disableBlend() noexcept
		{
			glDisable(GL_BLEND);
		}
		inline static void setBlendFunction(const BlendType source, const BlendType destination) noexcept
		{
			glBlendFunc(static_cast<GLenum>(source), static_cast<GLenum>(destination));
		}
		inline static void setBlendFunction(const BlendType sourceRgb, const BlendType destinationRgb,
			const BlendType sourceAlpha, const BlendType destinationAlpha) noexcept
		{
			glBlendFuncSeparate(static_cast<GLenum>(sourceRgb), static_cast<GLenum>(destinationRgb),
				static_cast<GLenum>(sourceAlpha), static_cast<GLenum>(destinationAlpha));
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

		inline const uint32_t getProgram() const noexcept
		{
			return program;
		}
		inline const int32_t getUniformLocation(const std::string& name) const
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

		virtual void setModelMatrix(const glm::mat4& value) const
		{}
		virtual void setViewMatrix(const glm::mat4& value) const
		{}
		virtual void setProjMatrix(const glm::mat4& value) const
		{}
		virtual void setViewProjMatrix(const glm::mat4& value) const
		{}
		virtual void setMvpMatrix(const glm::mat4& value) const
		{}
	};
}
