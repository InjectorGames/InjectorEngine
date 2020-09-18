#include "Injector/Graphics/GlDiffuseGpuPipeline.hpp"
#include "Injector/Storage/FileStream.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
    GlDiffuseGpuPipeline::GlDiffuseGpuPipeline(
        const std::shared_ptr<GlGpuShader>& vertexShader,
		const std::shared_ptr<GlGpuShader>& fragmentShader,
        const Vector4& objectColor,
        const Vector4& ambientColor,
        const Vector4& lightColor,
        const Vector3& lightDirection) :
        GlGpuPipeline(GL_TRIANGLES),
		ubo(objectColor, ambientColor, lightColor,
			lightDirection.getNormalized())
    {
		if (!vertexShader || !fragmentShader)
			throw NullException("GlDiffuseGpuPipeline", "GlDiffuseGpuPipeline", "shader");	

		glAttachShader(program, vertexShader->getShader());
		glAttachShader(program, fragmentShader->getShader());
		glLinkProgram(program);
		glDetachShader(program, vertexShader->getShader());
		glDetachShader(program, fragmentShader->getShader());

		if (!getLinkStatus(program))
		{
			auto log = getInfoLog(program);
			glDeleteProgram(program);

			throw Exception("GlDiffuseGpuPipeline", "GlDiffuseGpuPipeline",
				"Failed to link program, " + log);
		}

		mvpLocation = getUniformLocation(program, "u_MVP");
		normalLocation = getUniformLocation(program, "u_Normal");

		auto uniformBlockIndex = getUniformBlockIndex(program, "FragmentBufferObject");
		glUniformBlockBinding(program, uniformBlockIndex, 0);

		uniformBuffer = std::make_shared<GlGpuBuffer>(GpuBufferType::Uniform,
			sizeof(UniformBufferObject), GL_DYNAMIC_DRAW, nullptr);
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBuffer->getBuffer());
    }
    GlDiffuseGpuPipeline::~GlDiffuseGpuPipeline()
    {}

    const Vector4& GlDiffuseGpuPipeline::getObjectColor() const
    {
        return ubo.objectColor;
    }
	void GlDiffuseGpuPipeline::setObjectColor(const Vector4& _objectColor)
    {
        ubo.objectColor = Vector4(_objectColor);
    }

    const Vector4& GlDiffuseGpuPipeline::getAmbientColor() const
    {
        return ubo.ambientColor;
    }
	void GlDiffuseGpuPipeline::setAmbientColor(const Vector4& _ambientColor)
    {
        ubo.ambientColor = Vector4(_ambientColor);
    }

	const Vector4& GlDiffuseGpuPipeline::getLightColor() const
    {
        return ubo.lightColor;
    }
	void GlDiffuseGpuPipeline::setLightColor(const Vector4& _lightColor)
    {
        ubo.lightColor = Vector4(_lightColor);
    }

	const Vector3& GlDiffuseGpuPipeline::getLightDirection() const
    {
        return ubo.lightDirection;
    }
	void GlDiffuseGpuPipeline::setLightDirection(const Vector3& _lightDirection)
    {
        ubo.lightDirection = _lightDirection.getNormalized();
    }

	void GlDiffuseGpuPipeline::bind()	
	{
		GlGpuPipeline::bind();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glDisable(GL_STENCIL_TEST);
		glDisable(GL_BLEND);
		glCullFace(GL_BACK); 
		glFrontFace(GL_CW);
	}
    void GlDiffuseGpuPipeline::flush()
	{
		uniformBuffer->setData(&ubo, sizeof(UniformBufferObject));
	}
	void GlDiffuseGpuPipeline::setAttributes()
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		setVertexAttributePointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3) * 2);
		setVertexAttributePointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3) * 2, sizeof(Vector3));
	}

	void GlDiffuseGpuPipeline::setUniforms(
		const Matrix4& model,
		const Matrix4& view,
		const Matrix4& proj,
		const Matrix4& viewProj,
		const Matrix4& mvp)
	{
		setUniform(mvpLocation, mvp);
		setUniform(normalLocation, model.getInversed().getMatrix3(), GL_TRUE);
	}
}
