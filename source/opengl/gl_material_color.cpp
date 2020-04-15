#include <injector_engine/opengl.hpp>

namespace InjectorEngine
{
	GlMaterialColor::GlMaterialColor(gl::GLuint vertex, gl::GLuint fragment) :
		GlMaterial(vertex, fragment),
		mvpLocation(GetUniformLocation("u_MVP")),
		colorLocation(GetUniformLocation("u_Color"))
	{
		SetColor(glm::vec4(1.0f));
	}

	void GlMaterialColor::SetMVP(const glm::mat4& value) const
	{
		SetUniform(mvpLocation, value);
	}
	void GlMaterialColor::SetColor(const glm::vec4& value) const
	{
		SetUniform(colorLocation, value);
	}
}
