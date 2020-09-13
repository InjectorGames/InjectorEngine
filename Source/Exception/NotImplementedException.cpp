#include "Injector/Exception/NotImplementedException.hpp"

namespace Injector
{
    NotImplementedException::NotImplementedException(
        const std::string& className,
        const std::string& functionName) :
        Exception(className, functionName, "Not implemented")
    {}
    NotImplementedException::~NotImplementedException()
    {}
}
