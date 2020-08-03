#include <injector/byte_swap.hpp>

// TODO: get these defines from CMake

#if defined(_MSC_VER) && ( !defined(__clang__) || defined(__c2__) )

#include <cstdlib>
#define BYTE_SWAP_16(x) _byteswap_ushort(x)
#define BYTE_SWAP_32(x) _byteswap_ulong(x)
#define BYTE_SWAP_64(x) _byteswap_uint64(x)

#elif (defined(__clang__) && __has_builtin(__builtin_bswap32) && __has_builtin(__builtin_bswap64)) \
	|| (defined(__GNUC__ ) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)))

#if (defined(__clang__) && __has_builtin(__builtin_bswap16)) \
	|| (defined(__GNUC__) &&(__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)))
#define BYTE_SWAP_16(x) __builtin_bswap16(x)
#else
#define BYTE_SWAP_16(x) __builtin_bswap32((x) << 16)
#endif

#define BYTE_SWAP_32(x) __builtin_bswap32(x)
#define BYTE_SWAP_64(x) __builtin_bswap64(x)

#elif defined(__linux__)

#include <byteswap.h>
#define BYTE_SWAP_16(x) bswap_16(x)
#define BYTE_SWAP_32(x) bswap_32(x)
#define BYTE_SWAP_64(x) bswap_64(x)

#endif

namespace INJECTOR_NAMESPACE
{
	uint16_t ByteSwap::swapEndian(uint16_t value) noexcept
	{
		return static_cast<uint16_t>(BYTE_SWAP_16(value));
	}
	int16_t ByteSwap::swapEndian(int16_t value) noexcept
	{
		auto result = BYTE_SWAP_16(*reinterpret_cast<uint16_t*>(&value));
		return *reinterpret_cast<int16_t*>(&result);
	}
	uint32_t ByteSwap::swapEndian(uint32_t value) noexcept
	{
		return static_cast<uint32_t>(BYTE_SWAP_32(value));
	}
	int32_t ByteSwap::swapEndian(int32_t value) noexcept
	{
		auto result = BYTE_SWAP_32(*reinterpret_cast<uint32_t*>(&value));
		return *reinterpret_cast<int32_t*>(&result);
	}
	uint64_t ByteSwap::swapEndian(uint64_t value) noexcept
	{
		return static_cast<uint64_t>(BYTE_SWAP_64(value));
	}
	int64_t ByteSwap::swapEndian(int64_t value) noexcept
	{
		auto result = BYTE_SWAP_64(*reinterpret_cast<uint64_t*>(&value));
		return *reinterpret_cast<int64_t*>(&result);
	}
	float ByteSwap::swapEndian(float value) noexcept
	{
		auto result = BYTE_SWAP_32(*reinterpret_cast<uint32_t*>(&value));
		return *reinterpret_cast<float*>(&result);
	}
	double ByteSwap::swapEndian(double value) noexcept
	{
		auto result = BYTE_SWAP_64(*reinterpret_cast<uint64_t*>(&value));
		return *reinterpret_cast<double*>(&result);
	}

	uint16_t ByteSwap::swapBigEndian(uint16_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return value;
#else
		return swapEndian(value);
#endif
	}
	int16_t ByteSwap::swapBigEndian(int16_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return value;
#else
		return swapEndian(value);
#endif
	}
	uint32_t ByteSwap::swapBigEndian(uint32_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return value;
#else
		return swapEndian(value);
#endif
	}
	int32_t ByteSwap::swapBigEndian(int32_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return value;
#else
		return swapEndian(value);
#endif
	}
	uint64_t ByteSwap::swapBigEndian(uint64_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return value;
#else
		return swapEndian(value);
#endif
	}
	int64_t ByteSwap::swapBigEndian(int64_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return value;
#else
		return swapEndian(value);
#endif
	}
	float ByteSwap::swapBigEndian(float value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return value;
#else
		return swapEndian(value);
#endif
	}
	double ByteSwap::swapBigEndian(double value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return value;
#else
		return swapEndian(value);
#endif
	}

	uint16_t ByteSwap::swapLittleEndian(uint16_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return swapEndian(value);
#else
		return value;
#endif
	}
	int16_t ByteSwap::swapLittleEndian(int16_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return swapEndian(value);
#else
		return value;
#endif
	}
	uint32_t ByteSwap::swapLittleEndian(uint32_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return swapEndian(value);
#else
		return value;
#endif
	}
	int32_t ByteSwap::swapLittleEndian(int32_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return swapEndian(value);
#else
		return value;
#endif
	}
	uint64_t ByteSwap::swapLittleEndian(uint64_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return swapEndian(value);
#else
		return value;
#endif
	}
	int64_t ByteSwap::swapLittleEndian(int64_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return swapEndian(value);
#else
		return value;
#endif
	}
	float ByteSwap::swapLittleEndian(float value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return swapEndian(value);
#else
		return value;
#endif
	}
	double ByteSwap::swapLittleEndian(double value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return swapEndian(value);
#else
		return value;
#endif
	}
}
