#pragma once
#include <string>
#include <stdexcept>

namespace Injector
{
    class Exception : public std::exception
    {
    protected:
        std::string message;
    public:
        Exception(const std::string& className,
            const std::string& functionName,
            const std::string& message);
        virtual ~Exception();

        const char* what() const noexcept override;
    };
}
