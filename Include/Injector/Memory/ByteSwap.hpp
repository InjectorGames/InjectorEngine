#pragma once
#include <cstdint>
#include <cstdlib>

namespace Injector
{
	class ByteSwap final
	{
	 public:
		static uint16_t swapEndian(uint16_t value) noexcept;
		static int16_t swapEndian(int16_t value) noexcept;
		static uint32_t swapEndian(uint32_t value) noexcept;
		static int32_t swapEndian(int32_t value) noexcept;
		static uint64_t swapEndian(uint64_t value) noexcept;
		static int64_t swapEndian(int64_t value) noexcept;
		static size_t swapEndian(size_t value) noexcept;
		static float swapEndian(float value) noexcept;
		static double swapEndian(double value) noexcept;

		static uint16_t swapBigEndian(uint16_t value) noexcept;
		static int16_t swapBigEndian(int16_t value) noexcept;
		static uint32_t swapBigEndian(uint32_t value) noexcept;
		static int32_t swapBigEndian(int32_t value) noexcept;
		static uint64_t swapBigEndian(uint64_t value) noexcept;
		static int64_t swapBigEndian(int64_t value) noexcept;
		static size_t swapBigEndian(size_t value) noexcept;
		static float swapBigEndian(float value) noexcept;
		static double swapBigEndian(double value) noexcept;

		static uint16_t swapLittleEndian(uint16_t value) noexcept;
		static int16_t swapLittleEndian(int16_t value) noexcept;
		static uint32_t swapLittleEndian(uint32_t value) noexcept;
		static int32_t swapLittleEndian(int32_t value) noexcept;
		static uint64_t swapLittleEndian(uint64_t value) noexcept;
		static int64_t swapLittleEndian(int64_t value) noexcept;
		static size_t swapLittleEndian(size_t value) noexcept;
		static float swapLittleEndian(float value) noexcept;
		static double swapLittleEndian(double value) noexcept;
	};

}
