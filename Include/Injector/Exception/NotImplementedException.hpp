#pragma once
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
    class NotImplementedException : public Exception
    {
    public:
        NotImplementedException(const std::string& className,
            const std::string& functionName);
        virtual ~NotImplementedException();
    };
}
