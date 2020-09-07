#pragma once
#include "Injector/Exception.hpp"

namespace Injector
{
    class GraphicsException final : public Exception
    {
    public:
       GraphicsException(const std::string& message);
    };
}
