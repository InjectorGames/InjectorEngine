#include "Injector/Exception/NullException.hpp"

namespace Injector
{
    NullException::NullException(
        const std::string& className,
        const std::string& functionName,
        const std::string& variableName) :
        Exception(className, functionName,
            "Variable \"" + variableName +"\" is null")
    {}
    NullException::~NullException()
    {}
}
