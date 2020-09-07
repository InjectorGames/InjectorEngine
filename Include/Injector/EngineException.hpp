#pragma once
#include "Injector/Exception.hpp"

namespace Injector
{
    class EngineException final : public Exception
    {
    public:
        EngineException(const std::string& message);
    };
}
