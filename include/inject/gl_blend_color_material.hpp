#pragma once
#include <inject/gl_color_material.hpp>

namespace inject
{
	class GlBlendColorMaterial : public GlColorMaterial
	{
	public:
		inline static constexpr glm::vec4 defaultBlendColor = glm::vec4(1.0f, 1.0f, 1.0f, 0.5f);

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
