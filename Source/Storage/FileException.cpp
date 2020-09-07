#include "Injector/Storage/FileException.hpp"

namespace Injector
{
    FileException::FileException(
        const std::string& message,
        const std::string& filePath) :
        Exception("FileException: " + message + ", Path: " + filePath)
    {}
}
