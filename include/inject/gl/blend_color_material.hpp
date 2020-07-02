#pragma once
#include <inject/gl/color_material.hpp>

namespace INJECT_NAMESPACE
{
	class GlBlendColorMaterial : public GlColorMaterial
	{
	public:
		inline static const glm::vec4 defaultBlendColor = glm::vec4(1.0f, 1.0f, 1.0f, 0.5f);

		GlBlendColorMaterial(const std::shared_ptr<GlShader>& vertexShader,
			const std::shared_ptr<GlShader>& fragmentShader,
			const glm::vec4& color = defaultBlendColor) :
			GlColorMaterial(vertexShader, fragmentShader, color)
		{}

		void use() const override
		{
			enableDepthTest();
			enableBlend();
			setBlendFunction(BlendType::SrcAlpha, BlendType::OneMinusSrcAlpha);
			GlMaterial::use();
		}
	};
}
