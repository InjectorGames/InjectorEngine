#include "Injector/Exception.hpp"

namespace Injector
{
    Exception::Exception(const std::string& _message) :
        message(_message)
    {}
    Exception::~Exception()
    {}

    const char* Exception::what() const noexcept
    {
        return message.c_str();
    }
}
