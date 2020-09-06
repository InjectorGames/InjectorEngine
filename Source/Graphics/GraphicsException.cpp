#include "Injector/Graphics/GraphicsException.hpp"

namespace Injector::Graphics
{
    GraphicsException::GraphicsException(const string& message) :
        Exception("GraphicsException: " + message)
    {}
}
