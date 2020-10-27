#pragma once
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	// Cast exception class
	class CastException : public Exception
	{
	 public:
		// Creates a new cast exception
		CastException(
			const std::string& className,
			const std::string& functionName,
			const std::string& lineNumber,
			const std::string& variableName) noexcept;
	};
}
