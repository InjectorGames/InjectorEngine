#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	Exception::Exception(
		const std::string& className,
		const std::string& functionName,
		const std::string& lineNumber,
		const std::string& _message) noexcept :
		message(_message +
			" at " + className + "::" + functionName +
			"() at line " + lineNumber)
	{
	}

	const char* Exception::what() const noexcept
	{
		return message.c_str();
	}
}
