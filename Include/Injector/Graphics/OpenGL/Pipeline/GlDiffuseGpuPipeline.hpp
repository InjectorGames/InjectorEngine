#pragma once
#include "Injector/Graphics/OpenGL/GlGpuPipeline.hpp"
#include "Injector/Graphics/Pipeline/DiffuseGpuPipeline.hpp"
#include "Injector/Graphics/OpenGL/GlGpuBuffer.hpp"
#include "Injector/Graphics/OpenGL/GlGpuShader.hpp"

namespace Injector
{
	class GlDiffuseGpuPipeline :
		public GlGpuPipeline,
		public DiffuseGpuPipeline
	{
	 public:
		struct UniformBufferObject
		{
			Vector4 objectColor;
			Vector4 ambientColor;
			Vector4 lightColor;
			Vector3 lightDirection;
			float alignment;

			explicit UniformBufferObject(
				const Vector4& _objectColor = Vector4::one,
				const Vector4& _ambientColor = Vector4::one / 2.0f,
				const Vector4& _lightColor = Vector4::one,
				const Vector3& _lightDirection =
					Vector3(1.0f, 2.0f, 3.0f).getNormalized()) :
				objectColor(_objectColor),
				ambientColor(_ambientColor),
				lightColor(_lightColor),
				lightDirection(_lightDirection),
				alignment()
			{
			}
		};
	 protected:
		GLint mvpLocation;
		GLint normalLocation;
		std::shared_ptr<GlGpuBuffer> uniformBuffer;
		UniformBufferObject ubo;
	 public:
		GlDiffuseGpuPipeline(
			PrimitiveTopology primitiveTopology,
			const std::shared_ptr<GlGpuShader>& vertexShader,
			const std::shared_ptr<GlGpuShader>& fragmentShader,
			const UniformBufferObject& ubo = UniformBufferObject());

		const Vector4& getObjectColor() const override;
		void setObjectColor(const Vector4& objectColor) override;

		const Vector4& getAmbientColor() const override;
		void setAmbientColor(const Vector4& ambientColor) override;

		const Vector4& getLightColor() const override;
		void setLightColor(const Vector4& lightColor) override;

		const Vector3& getLightDirection() const override;
		void setLightDirection(const Vector3& lightDirection) override;

		void bind() override;
		void flush() override;
		void setAttributes() override;

		void setUniforms(
			const Matrix4& model,
			const Matrix4& view,
			const Matrix4& proj,
			const Matrix4& viewProj,
			const Matrix4& mvp) override;
	};
}
