#pragma once
#include "Injector/Exception.hpp"

namespace Injector
{
    class FileException final : public Exception
    {
    public:
        FileException(
            const std::string& message,
            const std::string& filePath);
    };
}
