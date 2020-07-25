#include <injector/shader.hpp>

namespace INJECTOR_NAMESPACE
{
	Shader::Shader(Type _type) :
		type(_type)
	{}
	Shader::~Shader()
	{}

	Shader::Type Shader::getType() const noexcept
	{
		return type;
	}
}
