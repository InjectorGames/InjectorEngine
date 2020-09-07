#include "Injector/EngineException.hpp"

namespace Injector
{
    EngineException::EngineException(const std::string& message) :
        Exception("EngineException: " + message)
    {}
}
