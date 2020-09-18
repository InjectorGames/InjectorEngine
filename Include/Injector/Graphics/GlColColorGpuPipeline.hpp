#pragma once
#include "Injector/Graphics/GlColorGpuPipeline.hpp"

namespace Injector
{
	class GlColColorGpuPipeline : public GlColorGpuPipeline
	{
	public:
		GlColColorGpuPipeline(
			const std::shared_ptr<GlGpuShader>& vertexShader,
			const std::shared_ptr<GlGpuShader>& fragmentShader,
			const Vector4& color = Vector4::one);
		virtual ~GlColColorGpuPipeline();

		void setAttributes() override;
	};
}
