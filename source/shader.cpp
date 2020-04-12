#include <injector_engine.hpp>

namespace Injector
{
	Shader::Shader(Type _type) : type(_type)
	{
		type = _type;
	}

	Shader::Type Shader::GetType()
	{
		return type;
	}
}
