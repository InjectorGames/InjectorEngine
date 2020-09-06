#include "Injector/EngineException.hpp"

namespace Injector
{
    EngineException::EngineException(const string& message) :
        Exception("EngineException: " + message)
    {}
}
