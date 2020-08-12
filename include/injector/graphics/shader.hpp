#pragma once
#include <injector/defines.hpp>
#include <injector/graphics/shader_stage.hpp>

#include <memory>

namespace INJECTOR_NAMESPACE
{
	class Shader
	{
	public:
		virtual ~Shader();
		virtual ShaderStage getStage() const;
	};

	using ShaderHandle = std::shared_ptr<Shader>;
}
