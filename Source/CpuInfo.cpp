#include "Injector/CpuInfo.hpp"
#include "Injector/Defines.hpp"

#if INJECTOR_SYSTEM_WINDOW
#define cpuid(info, id) __cpuid(info, id)
#elif INJECTOR_SYSTEM_LINUX || INJECTOR_SYSTEM_MACOS
#include <cpuid.h>
#define cpuid(info, id) __cpuid(id, info[0], info[1], info[2], info[3])
#endif

namespace Injector
{
	bool CpuInfo::sse = false;
	bool CpuInfo::sse2 = false;
	bool CpuInfo::sse3 = false;
	bool CpuInfo::ssse3 = false;
	bool CpuInfo::sse41 = false;
	bool CpuInfo::sse42 = false;

	void CpuInfo::initialize() noexcept
	{
		int cpuInfo[4];
		cpuid(cpuInfo, 0);

		if (cpuInfo[0] >= 0x00000001)
		{
			cpuid(cpuInfo, 0x00000001);
			sse = (cpuInfo[3] & ((int)1 << 25)) != 0;
			sse2 = (cpuInfo[3] & ((int)1 << 26)) != 0;
			sse3 = (cpuInfo[2] & ((int)1 << 0)) != 0;
			ssse3 = (cpuInfo[2] & ((int)1 << 9)) != 0;
			sse41 = (cpuInfo[2] & ((int)1 << 19)) != 0;
			sse42 = (cpuInfo[2] & ((int)1 << 20)) != 0;
		}
	}
	bool CpuInfo::hasSSE() noexcept
	{
		return sse;
	}
	bool CpuInfo::hasSSE2() noexcept
	{
		return sse2;
	}
	bool CpuInfo::hasSSE3() noexcept
	{
		return sse3;
	}
	bool CpuInfo::hasSSSE3() noexcept
	{
		return ssse3;
	}
	bool CpuInfo::hasSSE41() noexcept
	{
		return sse41;
	}
	bool CpuInfo::hasSSE42() noexcept
	{
		return sse42;
	}
}
