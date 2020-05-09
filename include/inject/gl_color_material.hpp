#pragma once
#include <inject/gl_material.hpp>

namespace inject
{
	class GlColorMaterial : public GlMaterial
	{
	protected:
		int32_t mvpLocation;
		int32_t colorLocation;
	public:
		GlColorMaterial(const std::shared_ptr<GlShader>& vertexShader,
			const std::shared_ptr<GlShader>& fragmentShader) :
			GlMaterial(vertexShader, fragmentShader)
		{
			mvpLocation = getUniformLocation("u_MVP");
			colorLocation = getUniformLocation("u_Color");

			use();
			setColor(glm::vec4(1.0f));
			unuse();
		}

		void setMVP(const glm::mat4& value) const override
		{
			setUniform(mvpLocation, value);
		}
		inline void setColor(const glm::vec4& value) const
		{
			setUniform(colorLocation, value);
		}
	};
}
