#pragma once
#include <inject/gl_material.hpp>

namespace inject
{
	// TODO: remake with this:
	// https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/simulating-sky/simulating-colors-of-the-sky
	// And use sphere or box, as skybox
	class GlGradientSkyMaterial : public GlMaterial
	{
	protected:
		int32_t pitchLocation;
		int32_t upColorLocation;
		int32_t downColorLocation;
	public:
		inline static const float defaultPitch = 0.0f;
		inline static const glm::vec3 defaultUpColor =
			glm::vec3(71.0f / 255.0f, 115.0f / 255.0f, 187.0f / 255.0f);
		inline static const glm::vec3 defaultDownColor =
			glm::vec3(135.0f / 255.0f, 164.0f / 255.0f, 211.0f / 255.0f);

		GlGradientSkyMaterial(const std::shared_ptr<GlShader>& vertexShader,
			const std::shared_ptr<GlShader>& fragmentShader) :
			GlMaterial(vertexShader, fragmentShader)
		{
			pitchLocation = getUniformLocation("u_Pitch");
			upColorLocation = getUniformLocation("u_UpColor");
			downColorLocation = getUniformLocation("u_DownColor");

			use();
			setPitch(defaultPitch);
			setUpColor(defaultUpColor);
			setDownColor(defaultDownColor);
			unuse();
		}

		void use() const override
		{
			enableDepthTest();
			disableBlend();
			GlMaterial::use();
		}

		inline void setPitch(const float value) const
		{
			setUniform(pitchLocation, value);
		}
		inline void setUpColor(const glm::vec3& value) const
		{
			setUniform(upColorLocation, value);
		}
		inline void setDownColor(const glm::vec3& value) const
		{
			setUniform(downColorLocation, value);
		}
	};
}
