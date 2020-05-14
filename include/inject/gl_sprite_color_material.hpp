#pragma once
#include <inject/gl_color_material.hpp>

namespace inject
{
	class GlSpriteColorMaterial : public GlColorMaterial
	{
	public:
		GlSpriteColorMaterial(const std::shared_ptr<GlShader>& vertexShader,
			const std::shared_ptr<GlShader>& fragmentShader,
			const glm::vec4& color = defaultColor) :
			GlColorMaterial(vertexShader, fragmentShader)
		{}

		void use() const override
		{
			disableDepthTest();
			disableBlend();
			GlMaterial::use();
		}
	};
}
