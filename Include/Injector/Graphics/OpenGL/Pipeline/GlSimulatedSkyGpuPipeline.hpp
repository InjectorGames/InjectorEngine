#pragma once
#include "Injector/Graphics/OpenGL/GlGpuPipeline.hpp"
#include "Injector/Graphics/Pipeline/SimulatedSkyGpuPipeline.hpp"
#include "Injector/Graphics/OpenGL/GlGpuBuffer.hpp"
#include "Injector/Graphics/OpenGL/GlGpuShader.hpp"

namespace Injector
{
	class GlSimulatedSkyGpuPipeline :
		public GlGpuPipeline,
		public SimulatedSkyGpuPipeline
	{
	 public:
		struct UniformBufferObject
		{
			float height;

			explicit UniformBufferObject(
				float _height) :
				height(_height)
			{
			}
		};
	 protected:
		std::shared_ptr<GlGpuBuffer> uniformBuffer;
		UniformBufferObject ubo;
	 public:
		GlSimulatedSkyGpuPipeline(
			GpuDrawMode drawMode,
			const std::shared_ptr<GlGpuShader>& vertexShader,
			const std::shared_ptr<GlGpuShader>& fragmentShader,
			const UniformBufferObject& ubo);

		float getHeight() const override;
		void setHeight(float height) override;

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
