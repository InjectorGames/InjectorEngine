#pragma once
#include "Injector/Defines.hpp"

#include <string>
#include <stdexcept>

#if INJECTOR_SYSTEM_LINUX || INJECTOR_SYSTEM_MACOS
#define THIS_FUNCTION_NAME std::string(__PRETTY_FUNCTION__)
#elif INJECTOR_SYSTEM_WINDOW
#define THIS_FUNCTION_NAME std::string(__FUNCSIG__)
#else
#error Unknown operating system
#endif



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
			const std::string& functionName,
			const std::string& message) noexcept;

		// Returns exception message
		const char* what() const noexcept override;
	};
}
