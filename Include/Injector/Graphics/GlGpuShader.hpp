#pragma once
#include "Injector/Graphics/GpuShader.hpp"
#include "Injector/Graphics/ShaderData.hpp"

#include "GL/glew.h"

#include <string>
#include <memory>

namespace Injector
{
	class GlGpuShader : public GpuShader
	{
	 protected:
		bool gles;
		GLuint shader;
		GLenum glStage;
	 public:
		static const std::string glHeader;
		static const std::string glesHeader;

		GlGpuShader(
			bool gles,
			GpuShaderStage stage,
			const std::shared_ptr<ShaderData>& data);
		virtual ~GlGpuShader();

		bool isGLES() const noexcept;
		GLuint getShader() const noexcept;
		GLenum getGlStage() const noexcept;

		static GLenum toGlStage(GpuShaderStage stage);
		static bool getCompileStatus(GLuint shader);
		static std::string getInfoLog(GLuint shader);
	};
}
