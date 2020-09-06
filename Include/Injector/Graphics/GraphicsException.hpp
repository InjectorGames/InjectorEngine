#pragma once
#include "Injector/Exception.hpp"

namespace Injector::Graphics
{
    class GraphicsException final : public Exception
    {
    public:
       GraphicsException(const string& message);
    };
}
