#pragma once

namespace Injector
{
    enum class GpuShaderStage
    {
        Vertex,
        TesselationControl,
        TesselationEvaluation,
        Geometry,
        Fragment,
        Compute,
        Raygen,
        AnyHit,
        ClosestHit,
        Miss,
        Intersection,
        Callable,
        Task,
        Mesh,
    };
}
