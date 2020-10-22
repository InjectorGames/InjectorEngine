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
				float _height = 1.0f) :
				height(_height)
			{
			}
		};
	 protected:
		std::shared_ptr<GlGpuBuffer> uniformBuffer;
		UniformBufferObject ubo;
	 public:
		GlSimulatedSkyGpuPipeline(
			PrimitiveTopology primitiveTopology,
			const std::shared_ptr<GlGpuShader>& vertexShader,
			const std::shared_ptr<GlGpuShader>& fragmentShader,
			const UniformBufferObject& ubo = UniformBufferObject());

		float getHeight() const override;
		void setHeight(float height) override;

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
