#pragma once
#include <injector/defines.hpp>
#include <injector/graphics/shader_stage.hpp>

#include <memory>

namespace INJECTOR_NAMESPACE
{
	class Shader
	{
	protected:
		ShaderStage stage;
	public:
		Shader(ShaderStage stage);
		virtual ~Shader();

		ShaderStage getStage() const noexcept;
	};

	using ShaderHandle = std::shared_ptr<Shader>;
}
