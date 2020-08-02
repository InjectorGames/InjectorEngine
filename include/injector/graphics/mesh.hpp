#pragma once
#include <injector/defines.hpp>
#include <memory>

namespace INJECTOR_NAMESPACE
{
	class Mesh
	{
	public:
		virtual ~Mesh();
		virtual void draw();
	};

	using MeshHandle = std::shared_ptr<Mesh>;
}
