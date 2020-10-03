#pragma once
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	class CastException : public Exception
	{
	 public:
		CastException(
			const std::string& className,
			const std::string& functionName,
			const std::string& variableName) noexcept;
	};
}
