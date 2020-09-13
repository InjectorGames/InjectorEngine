#include "Injector/Graphics/GlColorPipeline.hpp"
#include "Injector/Graphics/GlShader.hpp"
#include "Injector/Storage/FileStream.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	GlColorPipeline::GlColorPipeline(
		bool gles,
		const Vector4& _color) :
		GlPipeline(GL_TRIANGLES),
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

			throw Exception("GlColorPipeline", "GlColorPipeline",
				"Failed to link program, " + log);
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
	void GlColorPipeline::flush()
	{
		GlPipeline::bind();
		setUniform(colorLocation, color);
	}
	void GlColorPipeline::setAttributes()
	{
		glEnableVertexAttribArray(0);
		setVertexAttributePointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3));
	}

	void GlColorPipeline::setUniforms(
		const Matrix4& model,
		const Matrix4& view,
		const Matrix4& proj,
		const Matrix4& viewProj,
		const Matrix4& mvp)
	{
		setUniform(mvpLocation, mvp);
	}
}
