#pragma once
#include "Injector/Graphics/GpuShaderStage.hpp"

namespace Injector
{
    class GpuShader
    {
    protected:
        GpuShaderStage stage;
    public:
        GpuShader(GpuShaderStage stage);
        virtual ~GpuShader();

        GpuShaderStage getStage() const noexcept;
    };
}
