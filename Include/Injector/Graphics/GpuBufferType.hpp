#pragma once

namespace Injector
{
	enum class GpuBufferType
	{
		TransferSource,
		TransferDestination,
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
