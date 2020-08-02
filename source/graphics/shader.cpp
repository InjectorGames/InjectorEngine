#include <injector/graphics/shader.hpp>

namespace INJECTOR_NAMESPACE
{
	Shader::Shader(ShaderStage _stage) :
		stage(_stage)
	{}
	Shader::~Shader()
	{}

	ShaderStage Shader::getStage() const noexcept
	{
		return stage;
	}
}
