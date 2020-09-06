#pragma once
#include "Injector/Graphics/Pipeline.hpp"
#include "Injector/Graphics/GlVertexAttribute.hpp"

#include "GL/glew.h"

#include <string>
#include <vector>

namespace Injector::Graphics
{
	using namespace std;

	class GlPipeline : public Pipeline
	{
	protected:
		GLuint program;
		GLenum drawMode;
		vector<GlVertexAttribute> vertexAttributes;
	public:
		GlPipeline(GLenum drawMode,
			const vector<GlVertexAttribute>& vertexAttributes);
		virtual ~GlPipeline();

		GLuint getProgram() const noexcept;
		GLenum getDrawMode() const noexcept;
		const vector<GlVertexAttribute>& getVertexAttributes() const noexcept;

		virtual void flush();
		virtual void bind();

		static bool getLinkStatus(GLuint program) noexcept;
		static string getInfoLog(GLuint program) noexcept;
		static GLint getUniformLocation(GLuint program, const string& name);
	};
}
