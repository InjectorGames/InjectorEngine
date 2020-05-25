#pragma once

namespace inject
{
	class Shader
	{
	public:
		enum class Type
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
		};
	protected:
		Type type;
	public:
		Shader(const Type _type) :
			type(_type)
		{}

		inline const Type getType() const noexcept
		{
			return type;
		}
	};
}
