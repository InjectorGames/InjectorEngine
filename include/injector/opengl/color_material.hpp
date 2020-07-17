#pragma once
#include <inject/gl/material.hpp>

namespace INJECT_NAMESPACE
{
	class GlColorMaterial : public GlMaterial
	{
	protected:
		int32_t mvpMatrixLocation;
		int32_t colorLocation;
	public:
		inline static const glm::vec4 defaultColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		GlColorMaterial(const std::shared_ptr<GlShader>& vertexShader,
			const std::shared_ptr<GlShader>& fragmentShader,
			const glm::vec4& color = defaultColor) :
			GlMaterial(vertexShader, fragmentShader)
		{
			mvpMatrixLocation = getUniformLocation("u_MvpMatrix");
			colorLocation = getUniformLocation("u_Color");

			use();
			setColor(color);
			unuse();
		}

		void use() const override
		{
			enableDepthTest();
			disableBlend();
			GlMaterial::use();
		}

		void setMvpMatrix(const glm::mat4& value) const override
		{
			setUniform(mvpMatrixLocation, value);
		}
		inline void setColor(const glm::vec4& value) const
		{
			setUniform(colorLocation, value);
		}
	};
}
