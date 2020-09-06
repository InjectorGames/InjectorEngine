#pragma once
#include <string>
#include <stdexcept>

namespace Injector
{
    using namespace std;

    class Exception : public exception
    {
    protected:
        string message;
    public:
        Exception(const string& message);
        virtual ~Exception();

        const char* what() const noexcept override;
    };
}
