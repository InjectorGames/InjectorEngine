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
			FloatVector4 objectColor;
			FloatVector4 ambientColor;
			FloatVector4 lightColor;
			FloatVector3 lightDirection;
			float alignment;

			explicit UniformBufferObject(
				const FloatVector4& _objectColor,
				const FloatVector4& _ambientColor,
				const FloatVector4& _lightColor,
				const FloatVector3& _lightDirection) :
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
			GpuDrawMode drawMode,
			const std::shared_ptr<GlGpuShader>& vertexShader,
			const std::shared_ptr<GlGpuShader>& fragmentShader,
			const UniformBufferObject& ubo);

		const FloatVector4& getObjectColor() const override;
		void setObjectColor(const FloatVector4& objectColor) override;

		const FloatVector4& getAmbientColor() const override;
		void setAmbientColor(const FloatVector4& ambientColor) override;

		const FloatVector4& getLightColor() const override;
		void setLightColor(const FloatVector4& lightColor) override;

		const FloatVector3& getLightDirection() const override;
		void setLightDirection(const FloatVector3& lightDirection) override;

		void bind() override;
		void flush() override;
		void setAttributes() override;

		void setUniforms(
			const FloatMatrix4& model,
			const FloatMatrix4& view,
			const FloatMatrix4& proj,
			const FloatMatrix4& viewProj,
			const FloatMatrix4& mvp) override;
	};
}
