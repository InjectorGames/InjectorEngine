#include "Injector/Graphics/OpenGL/Pipeline/GlSimulatedSkyGpuPipeline.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	GlSimulatedSkyGpuPipeline::GlSimulatedSkyGpuPipeline(
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

	float GlSimulatedSkyGpuPipeline::getHeight() const
	{
		return ubo.height;
	}
	void GlSimulatedSkyGpuPipeline::setHeight(float height)
	{
		ubo.height = height;
	}

	void GlSimulatedSkyGpuPipeline::bind()
	{
		GlGpuPipeline::bind();
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
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
	void GlSimulatedSkyGpuPipeline::flush()
	{
		uniformBuffer->setData(
			&ubo,
			sizeof(UniformBufferObject));
	}
	void GlSimulatedSkyGpuPipeline::setAttributes()
	{
		glEnableVertexAttribArray(0);

		setVertexAttributePointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(FloatVector3),
			0);
	}

	void GlSimulatedSkyGpuPipeline::setUniforms(
		const FloatMatrix4& model,
		const FloatMatrix4& view,
		const FloatMatrix4& proj,
		const FloatMatrix4& viewProj,
		const FloatMatrix4& mvp)
	{
	}
}
