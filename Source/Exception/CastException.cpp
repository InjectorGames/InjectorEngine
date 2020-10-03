#include "Injector/Exception/CastException.hpp"

namespace Injector
{
	CastException::CastException(
		const std::string& className,
		const std::string& functionName,
		const std::string& variableName) noexcept :
		Exception(className, functionName,
			"Failed to cast \"" + variableName + "\"")
	{
	}
}
