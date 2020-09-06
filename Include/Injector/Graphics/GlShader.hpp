#pragma once
#include "GL/glew.h"

#include <string>
#include <vector>

namespace Injector::Graphics
{
	using namespace std;

	class GlShader
	{
	protected:
		GLuint shader;
		bool gles;
	public:
		static const string glHeader;
		static const string glesHeader;

		GlShader(GLenum stage,
			const string& source,
			bool gles);
		virtual ~GlShader();

		GLuint getShader() const noexcept;
		bool isGLES() const noexcept;

		static bool getCompileStatus(GLuint shader) noexcept;
		static string getInfoLog(GLuint shader) noexcept;
	};
}
