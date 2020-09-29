#pragma once
#include "Injector/Graphics/GpuShaderStage.hpp"
#include <vector>

namespace Injector
{
	struct ShaderData
	{
		std::vector<uint8_t> code;

		ShaderData();
		explicit ShaderData(const std::vector<uint8_t>& code);
		virtual ~ShaderData() = default;
	};
}
