#pragma once
#include <injector/graphics/shader.hpp>

#include <vector>
#include <string>
#include <cstdint>

#include <GL/glew.h>
#include <SDL_opengl.h>

namespace INJECTOR_NAMESPACE
{
	class GlShader : public Shader
	{
	protected:
		bool gles;
		GLenum stage;
		GLuint shader;

		static const std::string glHeader;
		static const std::string glesHeader;

		static bool getCompileStatus(GLuint shader) noexcept;
		static std::string getInfoLog(GLuint shader) noexcept;
	public:
		GlShader(bool gles, GLenum stage, const std::string& path);
		virtual ~GlShader();

		ShaderStage getStage() const override;

		bool getGLES() const noexcept;
		GLuint getShader() const noexcept;

		static GLenum toGlStage(ShaderStage stage);
		static ShaderStage toStage(GLenum stage);
	};

	using GlShaderHandle = std::shared_ptr<GlShader>;
}
