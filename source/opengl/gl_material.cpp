#include <injector_engine/opengl.hpp>

namespace InjectorEngine
{
	gl::GLuint GlMaterial::Create()
	{
		return gl::glCreateProgram();
	}
	void GlMaterial::Delete(gl::GLuint program)
	{
		gl::glDeleteProgram(program);
	}

	void GlMaterial::Attach(gl::GLuint program, gl::GLuint shader)
	{
		gl::glAttachShader(program, shader);
	}
	void GlMaterial::Detach(gl::GLuint program, gl::GLuint shader)
	{
		gl::glDetachShader(program, shader);
	}

	void GlMaterial::Link(gl::GLuint program)
	{
		gl::glLinkProgram(program);
	}
	bool GlMaterial::GetLinkStatus(gl::GLuint program)
	{
		gl::GLint success;
		gl::glGetProgramiv(program, gl::GL_LINK_STATUS, &success);
		return success;
	}
	std::string GlMaterial::GetInfoLog(gl::GLuint program)
	{
		gl::GLint length;
		gl::glGetProgramiv(program, gl::GL_INFO_LOG_LENGTH, &length);
		std::string infoLog(length, ' ');
		gl::glGetProgramInfoLog(program, length, &length, &infoLog[0]);
		return infoLog;
	}

	gl::GLint GlMaterial::GetUniformLocation(gl::GLuint program, const std::string& name)
	{
		auto location = gl::glGetUniformLocation(program, name.c_str());
		if (location == -1)
			throw std::runtime_error("Failed to get uniform location");
		return location;
	}

	void GlMaterial::SetUniform(gl::GLint index, gl::GLint value)
	{
		gl::glUniform1i(index, value);
	}
	void GlMaterial::SetUniform(gl::GLint index, gl::GLfloat value)
	{
		gl::glUniform1f(index, value);
	}
	void GlMaterial::SetUniform(gl::GLint index, const glm::vec2& value)
	{
		gl::glUniform2fv(index, 1, glm::value_ptr(value));
	}
	void GlMaterial::SetUniform(gl::GLint index, const glm::vec3& value)
	{
		gl::glUniform3fv(index, 1, glm::value_ptr(value));
	}
	void GlMaterial::SetUniform(gl::GLint index, const glm::vec4& value)
	{
		gl::glUniform4fv(index, 1, glm::value_ptr(value));
	}
	void GlMaterial::SetUniform(gl::GLint index, const glm::mat2& value)
	{
		gl::glUniformMatrix2fv(index, 1, gl::GL_FALSE, glm::value_ptr(value));
	}
	void GlMaterial::SetUniform(gl::GLint index, const glm::mat3& value)
	{
		gl::glUniformMatrix3fv(index, 1, gl::GL_FALSE, glm::value_ptr(value));
	}
	void GlMaterial::SetUniform(gl::GLint index, const glm::mat4& value)
	{
		gl::glUniformMatrix4fv(index, 1, gl::GL_FALSE, glm::value_ptr(value));
	}

	GlMaterial::GlMaterial(gl::GLuint shader) : program(Create())
	{
		Attach(program, shader);
		Link(program);
		Detach(program, shader);

		if (!GetLinkStatus(program))
		{
			auto infoLog = GetInfoLog(program);
			throw std::runtime_error("Failed to link OpenGL program. " + infoLog);
		}
	}
	GlMaterial::GlMaterial(gl::GLuint shader1, gl::GLuint shader2) : program(Create())
	{
		Attach(program, shader1);
		Attach(program, shader2);
		Link(program);
		Detach(program, shader2);
		Detach(program, shader1);

		if (!GetLinkStatus(program))
		{
			auto infoLog = GetInfoLog(program);
			throw std::runtime_error("Failed to link OpenGL program. " + infoLog);
		}
	}
	GlMaterial::GlMaterial(gl::GLuint shader1, gl::GLuint shader2, gl::GLuint shader3) : program(Create())
	{
		Attach(program, shader1);
		Attach(program, shader2);
		Attach(program, shader3);
		Link(program);
		Detach(program, shader3);
		Detach(program, shader2);
		Detach(program, shader1);

		if (!GetLinkStatus(program))
		{
			auto infoLog = GetInfoLog(program);
			throw std::runtime_error("Failed to link OpenGL program. " + infoLog);
		}
	}
	GlMaterial::GlMaterial(gl::GLuint shader1, gl::GLuint shader2, gl::GLuint shader3, gl::GLuint shader4) : program(Create())
	{
		Attach(program, shader1);
		Attach(program, shader2);
		Attach(program, shader3);
		Attach(program, shader4);
		Link(program);
		Attach(program, shader4);
		Detach(program, shader3);
		Detach(program, shader2);
		Detach(program, shader1);

		if (!GetLinkStatus(program))
		{
			auto infoLog = GetInfoLog(program);
			throw std::runtime_error("Failed to link OpenGL program. " + infoLog);
		}
	}

	GlMaterial::~GlMaterial()
	{
		Delete(program);
	}

	gl::GLint GlMaterial::GetUniformLocation(const std::string& name) const
	{
		return GetUniformLocation(program, name);
	}
}
