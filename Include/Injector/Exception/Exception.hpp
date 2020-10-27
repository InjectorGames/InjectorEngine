#pragma once
#include <string>
#include <stdexcept>

namespace Injector
{
	// Fatal exception class
	class Exception : public std::exception
	{
	 protected:
		// Exception details
		std::string message;
	 public:
		// Creates a new exception
		Exception(
			const std::string& className,
			const std::string& functionName,
			const std::string& lineNumber,
			const std::string& message) noexcept;

		// Returns exception message
		const char* what() const noexcept override;
	};
}
