#pragma once
#include <injector/graphics/shader.hpp>
#include <GL/glew.h>

#include <vector>
#include <string>
#include <cstdint>

namespace INJECTOR_NAMESPACE
{
	class GlShader : public Shader
	{
	protected:
		bool gles;
		GLuint shader;

		static const std::string glHeader;
		static const std::string glesHeader;

		static bool getCompileStatus(GLuint shader) noexcept;
		static std::string getInfoLog(GLuint shader) noexcept;
	public:
		GlShader(bool gles,
			const std::string& path,
			ShaderStage stage);
		virtual ~GlShader();

		bool getGLES() const noexcept;
		GLuint getShader() const noexcept;

		static GLenum toGlStage(ShaderStage stage);
		static ShaderStage toStage(GLenum stage);
	};

	using GlShaderHandle = std::shared_ptr<GlShader>;
}
