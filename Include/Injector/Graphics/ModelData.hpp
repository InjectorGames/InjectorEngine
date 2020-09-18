#pragma once
#include <string>

namespace Injector
{
    class Model
    {
    public:
        Model(const std::string& filePath);
        virtual ~Model();
    };
}