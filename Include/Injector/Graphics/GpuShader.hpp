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
		GpuShader(const GpuShader& shader) = delete;
		GpuShader(GpuShader&& shader) = delete;
		virtual ~GpuShader() = default;

		GpuShaderStage getStage() const noexcept;
	};
}
