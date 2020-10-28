#pragma once
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	// Null exception class
	class NullException : public Exception
	{
	 public:
		// Creates a new null exception
		NullException(
			const std::string& functionName,
			const std::string& variableName) noexcept;
	};
}
