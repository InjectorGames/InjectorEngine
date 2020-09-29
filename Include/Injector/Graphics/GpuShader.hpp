#pragma once
#include "Injector/Graphics/GpuShaderStage.hpp"

namespace Injector
{
	class GpuShader
	{
	 protected:
		GpuShaderStage stage;
	 public:
		explicit GpuShader(GpuShaderStage stage);
		virtual ~GpuShader() = default;

		GpuShaderStage getStage() const noexcept;
	};
}
