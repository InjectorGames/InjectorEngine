#pragma once
#include "Injector/Exception/Exception.hpp"

#include <cstdint>
#include <cstdlib>

namespace Injector
{
	// Out of range exception class
	class OutOfRangeException : public Exception
	{
	 public:
		// Creates a new out of range exception
		OutOfRangeException(
			const std::string& functionName,
			char value, char range) noexcept;
		// Creates a new out of range exception
		OutOfRangeException(
			const std::string& functionName,
			uint8_t value, uint8_t range) noexcept;
		// Creates a new out of range exception
		OutOfRangeException(
			const std::string& functionName,
			int8_t value, int8_t range) noexcept;
		// Creates a new out of range exception
		OutOfRangeException(
			const std::string& functionName,
			uint16_t value, uint16_t range) noexcept;
		// Creates a new out of range exception
		OutOfRangeException(
			const std::string& functionName,
			int16_t value, int16_t range) noexcept;
		// Creates a new out of range exception
		OutOfRangeException(
			const std::string& functionName,
			uint32_t value, uint32_t range) noexcept;
		// Creates a new out of range exception
		OutOfRangeException(
			const std::string& functionName,
			int32_t value, int32_t range) noexcept;
		// Creates a new out of range exception
		OutOfRangeException(
			const std::string& functionName,
			uint64_t value, uint64_t range) noexcept;
		// Creates a new out of range exception
		OutOfRangeException(
			const std::string& functionName,
			int64_t value, int64_t range) noexcept;
		// Creates a new out of range exception
		OutOfRangeException(
			const std::string& functionName,
			float value, float range) noexcept;
		// Creates a new out of range exception
		OutOfRangeException(
			const std::string& functionName,
			double value, double range) noexcept;
		// Creates a new out of range exception
		OutOfRangeException(
			const std::string& functionName,
			long double value, long double range) noexcept;
	};
}
