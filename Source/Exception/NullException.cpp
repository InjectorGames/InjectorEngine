#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	NullException::NullException(
		const std::string& functionName,
		const std::string& variableName) noexcept :
		Exception(functionName,
			"Variable \"" + variableName + "\" is null")
	{
	}
}
