#pragma once

namespace Injector
{
	enum class GpuBufferType
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
