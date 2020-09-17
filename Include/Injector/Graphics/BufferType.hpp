#pragma once

namespace Injector
{
    enum class BufferType
    {
        UniformTexel,
        StorageTexel,
        Uniform,
        Storage,
        Index,
        Vertex,
        Indirect,
        TransformFeedback,
        TransformFeedbackCounter,
    };
}