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
		FloatVector4 color;
	 public:
		// Creates a new color pipeline
		GlColorGpuPipeline(
			GpuDrawMode drawMode,
			const std::shared_ptr<GlGpuShader>& vertexShader,
			const std::shared_ptr<GlGpuShader>& fragmentShader,
			const FloatVector4& color);

		// Returns color value
		const FloatVector4& getColor() const override;
		// Sets color value
		void setColor(const FloatVector4& color) override;


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
