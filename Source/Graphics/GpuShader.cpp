#include "Injector/Graphics/GpuShader.hpp"

namespace Injector
{
	GpuShader::GpuShader(
		GpuShaderStage _stage) :
		stage(_stage)
	{
	}

	GpuShaderStage GpuShader::getStage() const noexcept
	{
		return stage;
	}
}
