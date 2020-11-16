#include "Injector/Graphics/OpenGL/Pipeline/GlGuiGpuPipeline.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	GlGuiGpuPipeline::GlGuiGpuPipeline(
		GpuDrawMode drawMode,
		const std::shared_ptr<GlGpuShader>& vertexShader,
		const std::shared_ptr<GlGpuShader>& fragmentShader,
		const std::shared_ptr<GlGpuImage>& _image,) :
		GlGpuPipeline(drawMode)
	{
		if (!vertexShader)
		{
			throw NullException(
				THIS_FUNCTION_NAME,
				"vertexShader");
		}
		if (!fragmentShader)
		{
			throw NullException(
				THIS_FUNCTION_NAME,
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
				THIS_FUNCTION_NAME,
				"Failed to link program, " + log);
		}

		projLocation = getUniformLocation(
			program,
			"u_Proj");
	}

	void GlGuiGpuPipeline::bind()
	{
		GlGpuPipeline::bind();
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glDisable(GL_SCISSOR_TEST);
		glDisable(GL_STENCIL_TEST);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(
			GL_SRC_ALPHA,
			GL_ONE_MINUS_SRC_ALPHA);
	}
	void GlGuiGpuPipeline::flush()
	{
	}
	void GlGuiGpuPipeline::setAttributes()
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		setVertexAttributePointer(
			0,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vector2),
			0);
		setVertexAttributePointer(
			1,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vector2) * 2,
			sizeof(Vector2));
		setVertexAttributePointer(
			2,
			4,
			GL_UNSIGNED_BYTE,
			GL_TRUE,
			sizeof(Vector2) * 2 + sizeof(Vector4),
			sizeof(Vector4));
		// TODO: replace Vector4 with ByteVector
	}

	void GlGuiGpuPipeline::setUniforms(
		const Matrix4& model,
		const Matrix4& view,
		const Matrix4& proj,
		const Matrix4& viewProj,
		const Matrix4& mvp)
	{
		setUniform(
			projLocation,
			proj);
	}
}
