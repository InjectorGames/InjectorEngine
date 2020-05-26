#pragma once
#include <inject/gl/diffuse_material.hpp>

namespace inject
{
	class GlBlendDiffuseMaterial : public GlDiffuseMaterial
	{
	public:
		inline static const glm::vec4 defaultBlendObjectColor = glm::vec4(1.0f, 1.0f, 1.0f, 0.5f);
		inline static const glm::vec4 defaultBlendAmbientColor = glm::vec4(0.25f, 0.25f, 0.25f, 1.0f);
		inline static const glm::vec4 defaultBlendLightColor = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);

		GlBlendDiffuseMaterial(const std::shared_ptr<GlShader>& vertexShader,
			const std::shared_ptr<GlShader>& fragmentShader,
			const glm::vec4& objectColor = defaultBlendObjectColor,
			const glm::vec4& ambientColor = defaultBlendAmbientColor,
			const glm::vec4& lightColor = defaultBlendLightColor,
			const glm::vec3& lightDirection = defaultLightDirection) :
			GlDiffuseMaterial(vertexShader, fragmentShader,
				objectColor, ambientColor, lightColor, lightDirection)
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
