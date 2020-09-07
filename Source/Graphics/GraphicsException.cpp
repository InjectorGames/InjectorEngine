#include "Injector/Graphics/GraphicsException.hpp"

namespace Injector
{
    GraphicsException::GraphicsException(const std::string& message) :
        Exception("GraphicsException: " + message)
    {}
}
