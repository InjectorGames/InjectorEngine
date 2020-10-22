#include "Injector/Graphics/OpenGL/Pipeline/GlColorGpuPipeline.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	GlColorGpuPipeline::GlColorGpuPipeline(
		GpuDrawMode drawMode,
		const std::shared_ptr<GlGpuShader>& vertexShader,
		const std::shared_ptr<GlGpuShader>& fragmentShader,
		const Vector4& _color) :
		GlGpuPipeline(drawMode),
		color(_color)
	{
		if (!vertexShader)
		{
			throw NullException(
				"GlColorGpuPipeline",
				"GlColorGpuPipeline",
				"vertexShader");
		}
		if (!fragmentShader)
		{
			throw NullException(
				"GlColorGpuPipeline",
				"GlColorGpuPipeline",
				"fragmentShader");
		}

		glAttachShader(
			program,
			vertexShader->getShader());
		glAttachShader(
			program,
			fragmentShader->getShader());

		glLinkProgram(program);

		glDetachShader(
			program,
			vertexShader->getShader());
		glDetachShader(
			program,
			fragmentShader->getShader());

		if (!getLinkStatus(program))
		{
			auto log = getInfoLog(program);
			glDeleteProgram(program);

			throw Exception(
				"GlColorGpuPipeline",
				"GlColorGpuPipeline",
				"Failed to link program, " + log);
		}

		mvpLocation = getUniformLocation(
			program,
			"u_MVP");
		colorLocation = getUniformLocation(
			program,
			"u_Color");
	}

	const Vector4& GlColorGpuPipeline::getColor() const
	{
		return color;
	}
	void GlColorGpuPipeline::setColor(const Vector4& _color)
	{
		color = Vector4(_color);
	}

	void GlColorGpuPipeline::bind()
	{
		GlGpuPipeline::bind();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glDisable(GL_STENCIL_TEST);
		glDisable(GL_BLEND);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);
	}
	void GlColorGpuPipeline::flush()
	{
		GlGpuPipeline::bind();
		setUniform(colorLocation, color);
	}
	void GlColorGpuPipeline::setAttributes()
	{
		glEnableVertexAttribArray(0);

		setVertexAttributePointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vector3),
			0);
	}

	void GlColorGpuPipeline::setUniforms(
		const Matrix4& model,
		const Matrix4& view,
		const Matrix4& proj,
		const Matrix4& viewProj,
		const Matrix4& mvp)
	{
		setUniform(
			mvpLocation,
			mvp);
	}
}
