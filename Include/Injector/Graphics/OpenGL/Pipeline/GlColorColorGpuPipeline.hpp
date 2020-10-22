#pragma once
#include "GlColorGpuPipeline.hpp"

namespace Injector
{
	class GlColorColorGpuPipeline : public GlColorGpuPipeline
	{
	 public:
		GlColorColorGpuPipeline(
			PrimitiveTopology primitiveTopology,
			const std::shared_ptr<GlGpuShader>& vertexShader,
			const std::shared_ptr<GlGpuShader>& fragmentShader,
			const Vector4& color = Vector4::one);

		void setAttributes() override;
	};
}
