#pragma once
#include "Injector/Graphics/OpenGL/GlGpuPipeline.hpp"
#include "Injector/Graphics/Pipeline/ColorGpuPipeline.hpp"
#include "Injector/Graphics/OpenGL/GlGpuShader.hpp"

namespace Injector
{
	// OpenGL color Graphics Processing Unit pipeline class
	class GlColorGpuPipeline :
		public GlGpuPipeline,
		public ColorGpuPipeline
	{
	 protected:
		// Model View Projection matrix location
		GLint mvpLocation;
		// Color vector location
		GLint colorLocation;

		// Color value
		Vector4 color;
	 public:
		// Creates a new color pipeline
		GlColorGpuPipeline(
			GpuDrawMode drawMode,
			const std::shared_ptr<GlGpuShader>& vertexShader,
			const std::shared_ptr<GlGpuShader>& fragmentShader,
			const Vector4& color);

		// Returns color value
		const Vector4& getColor() const override;
		// Sets color value
		void setColor(const Vector4& color) override;


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
