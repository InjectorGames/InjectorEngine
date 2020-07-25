#pragma once
#include <injector/shader.hpp>

#include <vector>
#include <string>
#include <cstdint>

namespace INJECTOR_NAMESPACE
{
	class GlShader : public Shader
	{
	protected:
		uint32_t instance;

		static uint32_t typeToEnum(const Type type);

		static uint32_t create(Type type) noexcept;
		static void destroy(uint32_t shader) noexcept;

		static void setSource(uint32_t shader, const char* source) noexcept;
		static void setSource(uint32_t shader,
			const std::vector<const char*>& sources) noexcept;

		static void compile(uint32_t shader) noexcept;
		static bool getCompileStatus(uint32_t shader) noexcept;
		static std::string getInfoLog(uint32_t shader) noexcept;
	public:
		GlShader(Type type, const std::vector<const char*>& sources);
		GlShader(Type type, const std::string& string, bool readFile);
		virtual ~GlShader();

		uint32_t getInstance() const noexcept;
	};
}
