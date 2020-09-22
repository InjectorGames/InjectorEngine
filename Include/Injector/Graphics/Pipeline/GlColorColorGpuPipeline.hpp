#pragma once
#include "Injector/Graphics/Pipeline/GlColorGpuPipeline.hpp"

namespace Injector
{
	class GlColorColorGpuPipeline : public GlColorGpuPipeline
	{
	 public:
		GlColorColorGpuPipeline(
			const std::shared_ptr<GlGpuShader>& vertexShader,
			const std::shared_ptr<GlGpuShader>& fragmentShader,
			const Vector4& color = Vector4::one);
		virtual ~GlColorColorGpuPipeline();

		void setAttributes() override;
	};
}
