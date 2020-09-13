#pragma once
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
    class NullException : public Exception
    {
    public:
        NullException(const std::string& className,
            const std::string& functionName,
            const std::string& variableName);
        virtual ~NullException();
    };
}
