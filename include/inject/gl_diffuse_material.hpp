#pragma once
#include <inject/gl_material.hpp>

namespace inject
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
		GlDiffuseMaterial(const std::shared_ptr<GlShader>& vertexShader,
			const std::shared_ptr<GlShader>& fragmentShader) :
			GlMaterial(vertexShader, fragmentShader)
		{
			mvpMatrixLocation = getUniformLocation("u_MvpMatrix");
			normalMatrixLocation = getUniformLocation("u_NormalMatrix");
			objectColorLocation = getUniformLocation("u_ObjectColor");
			ambientColorLocation = getUniformLocation("u_AmbientColor");
			lightColorLocation = getUniformLocation("u_LightColor");
			lightDirectionLocation = getUniformLocation("u_LightDirection");

			use();
			setObjectColor(glm::vec3(1.0f));
			setAmbientColor(glm::vec3(0.25f));
			setLightColor(glm::vec3(1.0f));
			setLightDirection(glm::vec3(-0.5f, -0.75f, -1.0f));
			unuse();
		}

		void setModelMatrix(const glm::mat4& value) const override
		{
			auto normalMatrix = glm::mat3(glm::transpose(glm::inverse(value)));
			setUniform(normalMatrixLocation, normalMatrix);
		}
		void setMvpMatrix(const glm::mat4& value) const override
		{
			setUniform(mvpMatrixLocation, value);
		}
		inline void setObjectColor(const glm::vec3& value) const
		{
			setUniform(objectColorLocation, value);
		}
		inline void setAmbientColor(const glm::vec3& value) const
		{
			setUniform(ambientColorLocation, value);
		}
		inline void setLightColor(const glm::vec3& value) const
		{
			setUniform(lightColorLocation, value);
		}
		inline void setLightDirection(const glm::vec3& value) const
		{
			setUniform(lightDirectionLocation, glm::normalize(value));
		}
	};
}
