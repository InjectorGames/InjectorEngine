#include <injector/graphics/gl_material.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	uint32_t GlMaterial::create() noexcept
	{
		return static_cast<uint32_t>(glCreateProgram());
	}
	void GlMaterial::destroy(uint32_t program) noexcept
	{
		glDeleteProgram(static_cast<GLuint>(program));
	}
	void GlMaterial::use(uint32_t program) noexcept
	{
		glUseProgram(static_cast<GLuint>(program));
	}

	void GlMaterial::attach(uint32_t program, uint32_t shader) noexcept
	{
		glAttachShader(static_cast<GLuint>(program), static_cast<GLuint>(shader));
	}
	void GlMaterial::detach(uint32_t program, uint32_t shader) noexcept
	{
		glDetachShader(static_cast<GLuint>(program), static_cast<GLuint>(shader));
	}

	void GlMaterial::link(uint32_t program) noexcept
	{
		glLinkProgram(static_cast<GLuint>(program));
	}
	bool GlMaterial::getLinkStatus(uint32_t program) noexcept
	{
		GLint success;
		glGetProgramiv(static_cast<GLuint>(program), GL_LINK_STATUS, &success);
		return success == GL_TRUE;
	}
	std::string GlMaterial::getInfoLog(uint32_t program) noexcept
	{
		GLint length;
		glGetProgramiv(static_cast<GLuint>(program), GL_INFO_LOG_LENGTH, &length);
		std::string infoLog(static_cast<size_t>(length), ' ');
		glGetProgramInfoLog(static_cast<GLuint>(program), length, &length,
			static_cast<GLchar*>(infoLog.data()));
		return infoLog;
	}

	int32_t GlMaterial::getUniformLocation(uint32_t program, const std::string& name)
	{
		auto location = static_cast<GLint>(glGetUniformLocation(
			static_cast<GLuint>(program), static_cast<const GLchar*>(name.c_str())));
		if (location == -1)
			throw std::runtime_error("Failed to get uniform location");
		return location;
	}

	void GlMaterial::setUniform(int32_t index, int value) noexcept
	{
		glUniform1i(static_cast<GLint>(index), static_cast<GLint>(value));
	}
	void GlMaterial::setUniform(int32_t index, float value) noexcept
	{
		glUniform1f(static_cast<GLint>(index), static_cast<GLfloat>(value));
	}
	void GlMaterial::setUniform(int32_t index, const Vector2& vector) noexcept
	{
		glUniform2fv(static_cast<GLint>(index), GL_ONE,
			reinterpret_cast<const GLfloat*>(&vector));
	}
	void GlMaterial::setUniform(int32_t index, const Vector3& vector) noexcept
	{
		glUniform3fv(static_cast<GLint>(index), GL_ONE, 
			reinterpret_cast<const GLfloat*>(&vector));
	}
	void GlMaterial::setUniform(int32_t index, const Vector4& vector) noexcept
	{
		glUniform4fv(static_cast<GLint>(index), GL_ONE,
			reinterpret_cast<const GLfloat*>(&vector));
	}
	void GlMaterial::setUniform(int32_t index, const Matrix2& matrix) noexcept
	{
		glUniformMatrix2fv(static_cast<GLint>(index), GL_ONE, GL_FALSE,
			reinterpret_cast<const GLfloat*>(&matrix));
	}
	void GlMaterial::setUniform(int32_t index, const Matrix3& matrix) noexcept
	{
		glUniformMatrix3fv(static_cast<GLint>(index), GL_ONE, GL_FALSE,
			reinterpret_cast<const GLfloat*>(&matrix));
	}
	void GlMaterial::setUniform(int32_t index, const Matrix4& matrix) noexcept
	{
		glUniformMatrix4fv(static_cast<GLint>(index), GL_ONE, GL_FALSE,
			reinterpret_cast<const GLfloat*>(&matrix));
	}

	void GlMaterial::enableDepthTest() noexcept
	{
		glEnable(GL_DEPTH_TEST);
	}
	void GlMaterial::disableDepthTest() noexcept
	{
		glDisable(GL_DEPTH_TEST);
	}
	void GlMaterial::setDepthTestFunction(uint32_t function) noexcept
	{
		glDepthFunc(static_cast<GLenum>(function));
	}

	void GlMaterial::enableBlend() noexcept
	{
		glEnable(GL_BLEND);
	}
	void GlMaterial::disableBlend() noexcept
	{
		glDisable(GL_BLEND);
	}
	void GlMaterial::setBlendFunction(uint32_t source, uint32_t destination) noexcept
	{
		glBlendFunc(static_cast<GLenum>(source), static_cast<GLenum>(destination));
	}
	void GlMaterial::setBlendFunction(uint32_t sourceRgb, uint32_t destinationRgb,
		uint32_t sourceAlpha, uint32_t destinationAlpha) noexcept
	{
		glBlendFuncSeparate(static_cast<GLenum>(sourceRgb), static_cast<GLenum>(destinationRgb),
			static_cast<GLenum>(sourceAlpha), static_cast<GLenum>(destinationAlpha));
	}

	int32_t GlMaterial::getUniformLocation(const std::string& name)
	{
		return getUniformLocation(instance, name);
	}

	GlMaterial::GlMaterial(const GlShader& shader)
	{
		instance = create();
		attach(instance, shader.getShader());
		link(instance);
		detach(instance, shader.getShader());

		if (!getLinkStatus(instance))
		{
			destroy(instance);
			throw std::runtime_error("Failed to link OpenGL program: " +
				getInfoLog(instance));
		}
	}
	GlMaterial::GlMaterial(const GlShader& shader1,
		const GlShader& shader2)
	{
		instance = create();
		attach(instance, shader1.getShader());
		attach(instance, shader2.getShader());
		link(instance);
		detach(instance, shader2.getShader());
		detach(instance, shader1.getShader());

		if (!getLinkStatus(instance))
		{
			destroy(instance);
			throw std::runtime_error("Failed to link OpenGL program: " +
				getInfoLog(instance));
		}
	}
	GlMaterial::GlMaterial(const GlShader& shader1,
		const GlShader& shader2,
		const GlShader& shader3)
	{
		instance = create();
		attach(instance, shader1.getShader());
		attach(instance, shader2.getShader());
		attach(instance, shader3.getShader());
		link(instance);
		detach(instance, shader3.getShader());
		detach(instance, shader2.getShader());
		detach(instance, shader1.getShader());

		if (!getLinkStatus(instance))
		{
			destroy(instance);
			throw std::runtime_error("Failed to link OpenGL program: " +
				getInfoLog(instance));
		}
	}
	GlMaterial::GlMaterial(const GlShader& shader1,
		const GlShader& shader2,
		const GlShader& shader3,
		const GlShader& shader4)
	{
		instance = create();
		attach(instance, shader1.getShader());
		attach(instance, shader2.getShader());
		attach(instance, shader3.getShader());
		attach(instance, shader4.getShader());
		link(instance);
		detach(instance, shader4.getShader());
		detach(instance, shader3.getShader());
		detach(instance, shader2.getShader());
		detach(instance, shader1.getShader());

		if (!getLinkStatus(instance))
		{
			destroy(instance);
			throw std::runtime_error("Failed to link OpenGL program: " + 
				getInfoLog(instance));
		}
	}
	GlMaterial::~GlMaterial()
	{
		destroy(instance);
	}

	uint32_t GlMaterial::getInstance() const noexcept
	{
		return instance;
	}

	void GlMaterial::use()
	{
		use(instance);
	}
	void GlMaterial::unuse()
	{
		use(GL_ZERO);
	}
}
