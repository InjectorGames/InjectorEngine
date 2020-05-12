#pragma once
#include <inject/gl_color_material.hpp>

namespace inject
{
	class GlBlendColorMaterial : public GlColorMaterial
	{
	public:
		inline static constexpr glm::vec4 defaultTransColor = glm::vec4(1.0f, 1.0f, 1.0f, 0.5f);

		GlBlendColorMaterial(const std::shared_ptr<GlShader>& vertexShader,
			const std::shared_ptr<GlShader>& fragmentShader,
			const glm::vec4& color = defaultTransColor) :
			GlColorMaterial(vertexShader, fragmentShader, defaultTransColor)
		{}

		void use() const override
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			GlMaterial::use();
		}
	};
}
