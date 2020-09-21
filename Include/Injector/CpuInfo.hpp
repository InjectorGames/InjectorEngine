#pragma once

namespace Injector
{
	class CpuInfo final
	{
	 private:
		static bool sse;
		static bool sse2;
		static bool sse3;
		static bool ssse3;
		static bool sse41;
		static bool sse42;
	 public:
		static void initialize() noexcept;
		static bool hasSSE() noexcept;
		static bool hasSSE2() noexcept;
		static bool hasSSE3() noexcept;
		static bool hasSSSE3() noexcept;
		static bool hasSSE41() noexcept;
		static bool hasSSE42() noexcept;
	};
}
