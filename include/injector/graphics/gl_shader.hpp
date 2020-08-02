#pragma once
#include <injector/graphics/shader.hpp>

#include <vector>
#include <string>
#include <cstdint>

namespace INJECTOR_NAMESPACE
{
	class GlShader : public Shader
	{
	protected:
		bool gles;
		uint32_t instance;

		static const std::string glHeader;
		static const std::string glesHeader;

		static uint32_t stageToEnum(ShaderStage stage);

		static uint32_t create(ShaderStage stage);
		static void destroy(uint32_t shader) noexcept;

		static void setSource(uint32_t shader, const char* source) noexcept;
		static void setSource(uint32_t shader,
			const std::vector<const char*>& sources) noexcept;

		static void compile(uint32_t shader) noexcept;
		static bool getCompileStatus(uint32_t shader) noexcept;
		static std::string getInfoLog(uint32_t shader) noexcept;
	public:
		GlShader(ShaderStage stage, const std::vector<const char*>& sources);
		GlShader(bool gles, ShaderStage stage, const std::string& path);
		virtual ~GlShader();

		bool getGLES() const noexcept;
		uint32_t getInstance() const noexcept;
	};

	using GlShaderHandle = std::shared_ptr<GlShader>;
}
