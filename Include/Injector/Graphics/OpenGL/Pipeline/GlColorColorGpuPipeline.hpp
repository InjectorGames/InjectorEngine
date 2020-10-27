#pragma once
#include "GlColorGpuPipeline.hpp"

namespace Injector
{
	// OpenGL color color Graphics Processing Unit pipeline class
	class GlColorColorGpuPipeline : public GlColorGpuPipeline
	{
	 public:
		// Creates a new color color pipeline
		GlColorColorGpuPipeline(
			GpuDrawMode drawMode,
			const std::shared_ptr<GlGpuShader>& vertexShader,
			const std::shared_ptr<GlGpuShader>& fragmentShader,
			const Vector4& color);

		// Sets vertex attributes
		void setAttributes() override;
	};
}
