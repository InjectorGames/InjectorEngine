#pragma once

namespace Injector
{
	// Graphics Processing Unit buffer type
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
