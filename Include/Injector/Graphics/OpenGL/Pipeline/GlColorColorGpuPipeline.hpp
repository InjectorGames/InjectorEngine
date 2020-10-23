#pragma once
#include "GlColorGpuPipeline.hpp"

namespace Injector
{
	class GlColorColorGpuPipeline : public GlColorGpuPipeline
	{
	 public:
		GlColorColorGpuPipeline(
			GpuDrawMode drawMode,
			const std::shared_ptr<GlGpuShader>& vertexShader,
			const std::shared_ptr<GlGpuShader>& fragmentShader,
			const Vector4& color);

		void setAttributes() override;
	};
}
