#include "Injector/Exception/OutOfRangeException.hpp"

namespace Injector
{
	OutOfRangeException::OutOfRangeException(
		const std::string& className,
		const std::string& functionName,
		const std::string& lineNumber,
		char value, char range) noexcept :
		Exception(className, functionName, lineNumber,
			"Out of range [" + std::to_string(value) + ", " + std::to_string(range) + "]")
	{
	}
	OutOfRangeException::OutOfRangeException(
		const std::string& className,
		const std::string& functionName,
		const std::string& lineNumber,
		uint8_t value, uint8_t range) noexcept :
		Exception(className, functionName, lineNumber,
			"Out of range [" + std::to_string(value) + ", " + std::to_string(range) + "]")
	{
	}
	OutOfRangeException::OutOfRangeException(
		const std::string& className,
		const std::string& functionName,
		const std::string& lineNumber,
		int8_t value, int8_t range) noexcept :
		Exception(className, functionName, lineNumber,
			"Out of range [" + std::to_string(value) + ", " + std::to_string(range) + "]")
	{
	}
	OutOfRangeException::OutOfRangeException(
		const std::string& className,
		const std::string& functionName,
		const std::string& lineNumber,
		uint16_t value, uint16_t range) noexcept :
		Exception(className, functionName, lineNumber,
			"Out of range [" + std::to_string(value) + ", " + std::to_string(range) + "]")
	{
	}
	OutOfRangeException::OutOfRangeException(
		const std::string& className,
		const std::string& functionName,
		const std::string& lineNumber,
		int16_t value, int16_t range) noexcept :
		Exception(className, functionName, lineNumber,
			"Out of range [" + std::to_string(value) + ", " + std::to_string(range) + "]")
	{
	}
	OutOfRangeException::OutOfRangeException(
		const std::string& className,
		const std::string& functionName,
		const std::string& lineNumber,
		uint32_t value, uint32_t range) noexcept :
		Exception(className, functionName, lineNumber,
			"Out of range [" + std::to_string(value) + ", " + std::to_string(range) + "]")
	{
	}
	OutOfRangeException::OutOfRangeException(
		const std::string& className,
		const std::string& functionName,
		const std::string& lineNumber,
		int32_t value, int32_t range) noexcept :
		Exception(className, functionName, lineNumber,
			"Out of range [" + std::to_string(value) + ", " + std::to_string(range) + "]")
	{
	}
	OutOfRangeException::OutOfRangeException(
		const std::string& className,
		const std::string& functionName,
		const std::string& lineNumber,
		uint64_t value, uint64_t range) noexcept :
		Exception(className, functionName, lineNumber,
			"Out of range [" + std::to_string(value) + ", " + std::to_string(range) + "]")
	{
	}
	OutOfRangeException::OutOfRangeException(
		const std::string& className,
		const std::string& functionName,
		const std::string& lineNumber,
		int64_t value, int64_t range) noexcept :
		Exception(className, functionName, lineNumber,
			"Out of range [" + std::to_string(value) + ", " + std::to_string(range) + "]")
	{
	}
	OutOfRangeException::OutOfRangeException(
		const std::string& className,
		const std::string& functionName,
		const std::string& lineNumber,
		float value, float range) noexcept :
		Exception(className, functionName, lineNumber,
			"Out of range [" + std::to_string(value) + ", " + std::to_string(range) + "]")
	{
	}
	OutOfRangeException::OutOfRangeException(
		const std::string& className,
		const std::string& functionName,
		const std::string& lineNumber,
		double value, double range) noexcept :
		Exception(className, functionName, lineNumber,
			"Out of range [" + std::to_string(value) + ", " + std::to_string(range) + "]")
	{
	}
	OutOfRangeException::OutOfRangeException(
		const std::string& className,
		const std::string& functionName,
		const std::string& lineNumber,
		long double value, long double range) noexcept :
		Exception(className, functionName, lineNumber,
			"Out of range [" + std::to_string(value) + ", " + std::to_string(range) + "]")
	{
	}
}
