#pragma once
#include <inject/gl/material.hpp>

namespace INJECT_NAMESPACE
{
	class GlDiffuseMaterial : public GlMaterial
	{
	protected:
		int32_t mvpMatrixLocation;
		int32_t normalMatrixLocation;
		int32_t objectColorLocation;
		int32_t ambientColorLocation;
		int32_t lightColorLocation;
		int32_t lightDirectionLocation;
	public:
		inline static const glm::vec4 defaultObjectColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		inline static const glm::vec4 defaultAmbientColor = glm::vec4(0.25f, 0.25f, 0.25f, 1.0f);
		inline static const glm::vec4 defaultLightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		inline static const glm::vec3 defaultLightDirection = glm::vec3(0.25f, 0.5f, 0.75f);

		GlDiffuseMaterial(const std::shared_ptr<GlShader>& vertexShader,
			const std::shared_ptr<GlShader>& fragmentShader,
			const glm::vec4& objectColor = defaultObjectColor,
			const glm::vec4& ambientColor = defaultAmbientColor,
			const glm::vec4& lightColor = defaultLightColor,
			const glm::vec3& lightDirection = defaultLightDirection) :
			GlMaterial(vertexShader, fragmentShader)
		{
			mvpMatrixLocation = getUniformLocation("u_MvpMatrix");
			normalMatrixLocation = getUniformLocation("u_NormalMatrix");
			objectColorLocation = getUniformLocation("u_ObjectColor");
			ambientColorLocation = getUniformLocation("u_AmbientColor");
			lightColorLocation = getUniformLocation("u_LightColor");
			lightDirectionLocation = getUniformLocation("u_LightDirection");

			use();
			setObjectColor(objectColor);
			setAmbientColor(ambientColor);
			setLightColor(lightColor);
			setLightDirection(lightDirection);
			unuse();
		}

		void use() const override
		{
			enableDepthTest();
			disableBlend();
			GlMaterial::use();
		}

		void setModelMatrix(const glm::mat4& value) const override
		{
			auto normalMatrix = glm::mat3(glm::transpose(glm::inverse(value)));

			// FIX: fixed incorrect value_ptr behavior with mat3
			std::copy_n(&normalMatrix[1][0], 3, &normalMatrix[0][2] + 1);
			std::copy_n(&normalMatrix[2][0], 3, &normalMatrix[1][2]);

			setUniform(normalMatrixLocation, normalMatrix);
		}
		void setMvpMatrix(const glm::mat4& value) const override
		{
			setUniform(mvpMatrixLocation, value);
		}
		inline void setObjectColor(const glm::vec4& value) const
		{
			setUniform(objectColorLocation, value);
		}
		inline void setAmbientColor(const glm::vec4& value) const
		{
			setUniform(ambientColorLocation, value);
		}
		inline void setLightColor(const glm::vec4& value) const
		{
			setUniform(lightColorLocation, value);
		}
		inline void setLightDirection(const glm::vec3& value) const
		{
			setUniform(lightDirectionLocation, glm::normalize(value));
		}
	};
}
