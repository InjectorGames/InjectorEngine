#pragma once
#include "GL/glew.h"
#include <string>

namespace Injector
{
	class GlShader
	{
	protected:
		GLuint shader;
		bool gles;
	public:
		static const std::string glHeader;
		static const std::string glesHeader;

		GlShader(GLenum stage,
			const std::string& source,
			bool gles);
		virtual ~GlShader();

		GLuint getShader() const noexcept;
		bool isGLES() const noexcept;

		static bool getCompileStatus(GLuint shader) noexcept;
		static std::string getInfoLog(GLuint shader) noexcept;
	};
}
