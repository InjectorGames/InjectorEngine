#pragma once
#include <injector/defines.hpp>

namespace INJECTOR_NAMESPACE
{
	enum class BufferUsage
	{
		CpuOnly,
		GpuOnly,
		CpuToGpu,
		GpuToCpu,
		CpuCopy,
	};
}
