#pragma once
#include <injector/defines.hpp>
#include <memory>

namespace INJECTOR_NAMESPACE
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
		Shader(Type _type);
		virtual ~Shader();

		Type getType() const noexcept;
	};

	using ShaderHandle = std::shared_ptr<Shader>;
}
