#pragma once
#include <injector/defines.hpp>

namespace INJECTOR_NAMESPACE
{
	enum class ShaderStage
	{
		Vertex,
		TessellationControl,
		TessellationEvaluation,
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
