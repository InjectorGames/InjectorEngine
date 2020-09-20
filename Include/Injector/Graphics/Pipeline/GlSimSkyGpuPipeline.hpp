#pragma once
#include "Injector/Graphics/Pipeline/GlGpuPipeline.hpp"
#include "Injector/Graphics/Pipeline/SimSkyGpuPipeline.hpp"
#include "Injector/Graphics/GlGpuBuffer.hpp"
#include "Injector/Graphics/GlGpuShader.hpp"

namespace Injector
{
	class GlSimSkyGpuPipeline :
		public GlGpuPipeline,
		public SimSkyGpuPipeline
	{
	 public:
		struct UniformBufferObject
		{
			float height;

			UniformBufferObject(
				float _height) :
				height(_height)
			{
			}
		};
	 protected:
		std::shared_ptr<GlGpuBuffer> uniformBuffer;
		UniformBufferObject ubo;
	 public:
		GlSimSkyGpuPipeline(
			const std::shared_ptr<GlGpuShader>& vertexShader,
			const std::shared_ptr<GlGpuShader>& fragmentShader,
			float height = 1.0f);
		virtual ~GlSimSkyGpuPipeline();

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
