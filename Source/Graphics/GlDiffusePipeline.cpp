#include "Injector/Graphics/GlDiffusePipeline.hpp"
#include "Injector/Graphics/GlShader.hpp"
#include "Injector/Storage/FileStream.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
    GlDiffusePipeline::GlDiffusePipeline(
        bool gles,
        const Vector4& objectColor,
        const Vector4& ambientColor,
        const Vector4& lightColor,
        const Vector3& lightDirection) :
        GlPipeline(GL_TRIANGLES),
		ubo(objectColor, ambientColor, lightColor,
			lightDirection.getNormalized())
    {
        auto vertexSource = FileStream::readAllText(
			"Resources/Shaders/Diffuse.vert");
		auto vertexShader = GlShader(GL_VERTEX_SHADER, vertexSource, gles);

		auto fragmentSource = FileStream::readAllText(
			"Resources/Shaders/Diffuse.frag");
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

			throw Exception("GlDiffusePipeline", "GlDiffusePipeline",
				"Failed to link program, " + log);
		}

		mvpLocation = getUniformLocation(program, "u_MVP");
		normalLocation = getUniformLocation(program, "u_Normal");

		auto uniformBlockIndex = getUniformBlockIndex(program, "FragmentBufferObject");
		glUniformBlockBinding(program, uniformBlockIndex, 0);

		uniformBuffer = std::make_shared<GlBuffer>(BufferType::Uniform,
			sizeof(UniformBufferObject), GL_DYNAMIC_DRAW, nullptr);
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBuffer->getBuffer());
    }
    GlDiffusePipeline::~GlDiffusePipeline()
    {}

    const Vector4& GlDiffusePipeline::getObjectColor() const
    {
        return ubo.objectColor;
    }
	void GlDiffusePipeline::setObjectColor(const Vector4& _objectColor)
    {
        ubo.objectColor = Vector4(_objectColor);
    }

    const Vector4& GlDiffusePipeline::getAmbientColor() const
    {
        return ubo.ambientColor;
    }
	void GlDiffusePipeline::setAmbientColor(const Vector4& _ambientColor)
    {
        ubo.ambientColor = Vector4(_ambientColor);
    }

	const Vector4& GlDiffusePipeline::getLightColor() const
    {
        return ubo.lightColor;
    }
	void GlDiffusePipeline::setLightColor(const Vector4& _lightColor)
    {
        ubo.lightColor = Vector4(_lightColor);
    }

	const Vector3& GlDiffusePipeline::getLightDirection() const
    {
        return ubo.lightDirection;
    }
	void GlDiffusePipeline::setLightDirection(const Vector3& _lightDirection)
    {
        ubo.lightDirection = _lightDirection.getNormalized();
    }

	void GlDiffusePipeline::bind()	
	{
		GlPipeline::bind();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glDisable(GL_STENCIL_TEST);
		glDisable(GL_BLEND);
		glCullFace(GL_BACK); 
		glFrontFace(GL_CW);
	}
    void GlDiffusePipeline::flush()
	{
		uniformBuffer->setData(&ubo, sizeof(UniformBufferObject));
	}
	void GlDiffusePipeline::setAttributes()
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		setVertexAttributePointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3) * 2);
		setVertexAttributePointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3) * 2, sizeof(Vector3));
	}

	void GlDiffusePipeline::setUniforms(
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
