#pragma once
#include <inject/gl/color_material.hpp>

namespace INJECT_NAMESPACE
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
			enableBlend();
			setBlendFunction(BlendType::SrcAlpha, BlendType::OneMinusSrcAlpha);
			GlMaterial::use();
		}
	};
}
