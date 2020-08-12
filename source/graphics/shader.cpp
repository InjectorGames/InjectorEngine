#include <injector/graphics/shader.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	Shader::~Shader()
	{}

	ShaderStage Shader::getStage() const
	{
		throw std::runtime_error("Not implemented shader function");
	}
}
