#include "Injector/Exception/CastException.hpp"

namespace Injector
{
	CastException::CastException(
		const std::string& className,
		const std::string& functionName,
		const std::string& lineNumber,
		const std::string& variableName) noexcept :
		Exception(className, functionName, lineNumber,
			"Failed to cast \"" + variableName + "\"")
	{
	}
}
