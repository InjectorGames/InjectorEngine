#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	NullException::NullException(
		const std::string& className,
		const std::string& functionName,
		const std::string& variableName) noexcept :
		Exception(className, functionName,
			"Variable \"" + variableName + "\" is null")
	{
	}
}
