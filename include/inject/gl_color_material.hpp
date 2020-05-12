#pragma once
#include <inject/gl_material.hpp>

namespace inject
{
	class GlColorMaterial : public GlMaterial
	{
	protected:
		int32_t mvpMatrixLocation;
		int32_t colorLocation;
	public:
		inline static constexpr glm::vec3 defaultColor = glm::vec3(1.0f);

		GlColorMaterial(const std::shared_ptr<GlShader>& vertexShader,
			const std::shared_ptr<GlShader>& fragmentShader) :
			GlMaterial(vertexShader, fragmentShader)
		{
			mvpMatrixLocation = getUniformLocation("u_MvpMatrix");
			colorLocation = getUniformLocation("u_Color");

			use();
			setColor(glm::vec3(defaultColor));
			unuse();
		}

		void setMvpMatrix(const glm::mat4& value) const override
		{
			setUniform(mvpMatrixLocation, value);
		}
		inline void setColor(const glm::vec3& value) const
		{
			setUniform(colorLocation, value);
		}
	};
}
