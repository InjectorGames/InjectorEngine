#pragma once
#include "Injector/Exception.hpp"

namespace Injector::File
{
    class FileException final : public Exception
    {
    public:
        FileException(
            const string& message,
            const string& filePath);
    };
}
