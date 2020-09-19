#include "Injector/Graphics/Pipeline/GlSkyGpuPipeline.hpp"
#include "Injector/Storage/FileStream.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	GlSkyGpuPipeline::GlSkyGpuPipeline(
		const std::shared_ptr<GlGpuShader>& vertexShader,
		const std::shared_ptr<GlGpuShader>& fragmentShader,
		float height) :
		GlGpuPipeline(GL_TRIANGLES),
		ubo(height)
	{
		if (!vertexShader || !fragmentShader)
			throw NullException("GlSkyGpuPipeline", "GlSkyGpuPipeline", "shader");

		glAttachShader(program, vertexShader->getShader());
		glAttachShader(program, fragmentShader->getShader());
		glLinkProgram(program);
		glDetachShader(program, vertexShader->getShader());
		glDetachShader(program, fragmentShader->getShader());

		if (!getLinkStatus(program))
		{
			auto log = getInfoLog(program);
			glDeleteProgram(program);

			throw Exception("GlSkyGpuPipeline", "GlSkyGpuPipeline",
				"Failed to link program, " + log);
		}

		auto uniformBlockIndex = getUniformBlockIndex(program, "FragmentBufferObject");
		glUniformBlockBinding(program, uniformBlockIndex, 0);

		uniformBuffer = std::make_shared<GlGpuBuffer>(GpuBufferType::Uniform,
			sizeof(UniformBufferObject), GL_DYNAMIC_DRAW, nullptr);
	}
	GlSkyGpuPipeline::~GlSkyGpuPipeline()
	{
	}

	float GlSkyGpuPipeline::getHeight() const
	{
		return ubo.height;
	}
	void GlSkyGpuPipeline::setHeight(float height)
	{
		ubo.height = height;
	}

	void GlSkyGpuPipeline::bind()
	{
		GlGpuPipeline::bind();
		glEnable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_STENCIL_TEST);
		glDisable(GL_BLEND);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);

		glBindBufferBase(GL_UNIFORM_BUFFER, 0,
			uniformBuffer->getBuffer());
	}
	void GlSkyGpuPipeline::flush()
	{
		uniformBuffer->setData(&ubo, sizeof(UniformBufferObject));
	}
	void GlSkyGpuPipeline::setAttributes()
	{
		glEnableVertexAttribArray(0);

		setVertexAttributePointer(0, 3, GL_FLOAT, GL_FALSE,
			sizeof(Vector3), 0);
	}

	void GlSkyGpuPipeline::setUniforms(
		const Matrix4& model,
		const Matrix4& view,
		const Matrix4& proj,
		const Matrix4& viewProj,
		const Matrix4& mvp)
	{
	}
}
