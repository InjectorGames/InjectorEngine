#include "Injector/Graphics/GlColorPipeline.hpp"
#include "Injector/Storage/FileStream.hpp"
#include "Injector/Graphics/GraphicsException.hpp"
#include "Injector/Graphics/GlShader.hpp"

namespace Injector
{
	const std::vector<GlVertexAttribute> GlColorPipeline::vertexAttributes =
	{
		GlVertexAttribute(0, 3, GL_FLOAT, false, sizeof(Vector3), 0),
	};

	GlColorPipeline::GlColorPipeline(
		bool gles,
		const Vector4& _color) :
		GlPipeline(GL_TRIANGLES, vertexAttributes),
		color(_color)
	{
		auto vertexSource = FileStream::readAllText(
			"resources/shaders/color.vert");
		auto vertexShader = GlShader(GL_VERTEX_SHADER, vertexSource, gles);

		auto fragmentSource = FileStream::readAllText(
			"resources/shaders/color.frag");
		auto fragmentShader = GlShader(GL_FRAGMENT_SHADER, fragmentSource, gles);

		glAttachShader(program, vertexShader.getShader());
		glAttachShader(program, fragmentShader.getShader());
		glLinkProgram(program);
		glDetachShader(program, vertexShader.getShader());
		glDetachShader(program, fragmentShader.getShader());

		if (!getLinkStatus(program))
		{
			auto log = getInfoLog(program);
			glDeleteProgram(program);

			throw GraphicsException("Failed to link OpenGL program: " + log);
		}

		mvpLocation = getUniformLocation(program, "u_MVP");
		colorLocation = getUniformLocation(program, "u_Color");
	}
	GlColorPipeline::~GlColorPipeline()
	{}

	const Vector4& GlColorPipeline::getColor() const
	{
		return color;
	}
	void GlColorPipeline::setColor(const Vector4& _color)
	{
		color = Vector4(_color);
	}

	void GlColorPipeline::flush()
	{
		GlPipeline::bind();

		glUniform4fv(colorLocation, GL_ONE, 
			reinterpret_cast<const GLfloat*>(&color));
	}
	void GlColorPipeline::bind()
	{
		GlPipeline::bind();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glDisable(GL_STENCIL_TEST);
		glDisable(GL_BLEND);
		glCullFace(GL_BACK); 
		glFrontFace(GL_CW); 
	}

	void GlColorPipeline::setUniforms(
		const Matrix4& model,
		const Matrix4& view,
		const Matrix4& proj,
		const Matrix4& viewProj,
		const Matrix4& mvp)
	{
		glUniformMatrix4fv(mvpLocation, GL_ONE, GL_FALSE,
			reinterpret_cast<const GLfloat*>(&mvp));
	}
}
