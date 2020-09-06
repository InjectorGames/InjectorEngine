#include "Injector/File/FileException.hpp"

namespace Injector::File
{
    FileException::FileException(
        const string& message,
        const string& filePath) :
        Exception("FileException: " + message + ", Path: " + filePath)
    {}
}
