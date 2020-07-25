#pragma once
#include <injector/defines.hpp>

namespace INJECTOR_NAMESPACE
{
	class Mesh
	{
	public:
		virtual ~Mesh();
		virtual void draw();
	};
}
