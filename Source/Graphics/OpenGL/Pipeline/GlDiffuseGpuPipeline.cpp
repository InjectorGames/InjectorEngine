#include "Injector/Graphics/OpenGL/Pipeline/GlDiffuseGpuPipeline.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	GlDiffuseGpuPipeline::GlDiffuseGpuPipeline(
		GpuDrawMode drawMode,
		const std::shared_ptr<GlGpuShader>& vertexShader,
		const std::shared_ptr<GlGpuShader>& fragmentShader,
		const UniformBufferObject& _ubo) :
		GlGpuPipeline(drawMode),
		ubo(_ubo)
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

		mvpLocation = getUniformLocation(
			program,
			"u_MVP");
		normalLocation = getUniformLocation(
			program,
			"u_Normal");

		auto uniformBlockIndex = getUniformBlockIndex(
			program,
			"FragmentBufferObject");
		glUniformBlockBinding(
			program,
			uniformBlockIndex,
			0);

		uniformBuffer = std::make_shared<GlGpuBuffer>(
			GpuBufferType::Uniform,
			sizeof(UniformBufferObject),
			GL_DYNAMIC_DRAW,
			nullptr);
	}

	const FloatVector4& GlDiffuseGpuPipeline::getObjectColor() const
	{
		return ubo.objectColor;
	}
	void GlDiffuseGpuPipeline::setObjectColor(const FloatVector4& color)
	{
		ubo.objectColor = FloatVector4(color);
	}

	const FloatVector4& GlDiffuseGpuPipeline::getAmbientColor() const
	{
		return ubo.ambientColor;
	}
	void GlDiffuseGpuPipeline::setAmbientColor(const FloatVector4& color)
	{
		ubo.ambientColor = FloatVector4(color);
	}

	const FloatVector4& GlDiffuseGpuPipeline::getLightColor() const
	{
		return ubo.lightColor;
	}
	void GlDiffuseGpuPipeline::setLightColor(const FloatVector4& color)
	{
		ubo.lightColor = FloatVector4(color);
	}

	const FloatVector3& GlDiffuseGpuPipeline::getLightDirection() const
	{
		return ubo.lightDirection;
	}
	void GlDiffuseGpuPipeline::setLightDirection(const FloatVector3& direction)
	{
		ubo.lightDirection = direction.getNormalized();
	}

	void GlDiffuseGpuPipeline::bind()
	{
		GlGpuPipeline::bind();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glDisable(GL_SCISSOR_TEST);
		glDisable(GL_STENCIL_TEST);
		glDisable(GL_BLEND);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);

		glBindBufferBase(
			GL_UNIFORM_BUFFER,
			0,
			uniformBuffer->getBuffer());
	}
	void GlDiffuseGpuPipeline::flush()
	{
		uniformBuffer->setData(
			&ubo,
			sizeof(UniformBufferObject));
	}
	void GlDiffuseGpuPipeline::setAttributes()
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		setVertexAttributePointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(FloatVector3) * 2,
			0);
		setVertexAttributePointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(FloatVector3) * 2,
			sizeof(FloatVector3));
	}

	void GlDiffuseGpuPipeline::setUniforms(
		const FloatMatrix4& model,
		const FloatMatrix4& view,
		const FloatMatrix4& proj,
		const FloatMatrix4& viewProj,
		const FloatMatrix4& mvp)
	{
		auto normal = model.getInverted().getTransposed();

		setUniform(
			mvpLocation,
			mvp);
		setUniform(
			normalLocation,
			normal);
	}
}
