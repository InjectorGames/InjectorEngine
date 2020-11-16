#pragma once
#include "Injector/Graphics/OpenGL/GlGpuPipeline.hpp"
#include "Injector/Graphics/Pipeline/GuiGpuPipeline.hpp"
#include "Injector/Graphics/OpenGL/GlGpuShader.hpp"

namespace Injector
{
	class GlGuiGpuPipeline :
		public GlGpuPipeline,
		public ColorGpuPipeline
	{
	 protected:
		GLint projLocation;
	 public:
		GlGuiGpuPipeline(
			GpuDrawMode drawMode,
			const std::shared_ptr<GlGpuShader>& vertexShader,
			const std::shared_ptr<GlGpuShader>& fragmentShader);

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
