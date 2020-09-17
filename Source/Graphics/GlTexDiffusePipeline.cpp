#include "Injector/Graphics/GlTexDiffusePipeline.hpp"
#include "Injector/Graphics/GlShader.hpp"
#include "Injector/Storage/FileStream.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
    GlTexDiffusePipeline::GlTexDiffusePipeline(
        bool gles,
        const std::shared_ptr<GlTexture>& _texture,
        const Vector4& objectColor,
		const Vector4& ambientColor,
		const Vector4& lightColor,
		const Vector3& lightDirection,
        const Vector2& textureScale,
        const Vector2& textureOffset) :
        GlPipeline(GL_TRIANGLES),
        ubo(objectColor, ambientColor, lightColor,
			lightDirection.getNormalized(),
            textureScale, textureOffset),
        texture(_texture)
    {
        if(!_texture)
            throw NullException("GlTexDiffusePipeline", "GlTexDiffusePipeline", "texture");

        auto vertexSource = FileStream::readAllText(
			"Resources/Shaders/TexDiffuse.vert");
		auto vertexShader = GlShader(GL_VERTEX_SHADER, vertexSource, gles);

		auto fragmentSource = FileStream::readAllText(
			"Resources/Shaders/TexDiffuse.frag");
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

			throw Exception("GlTexDiffusePipeline", "GlTexDiffusePipeline",
				"Failed to link program, " + log);
		}

		mvpLocation = getUniformLocation(program, "u_MVP");
		normalLocation = getUniformLocation(program, "u_Normal");

		auto uniformBlockIndex = getUniformBlockIndex(program, "FragmentBufferObject");
		glUniformBlockBinding(program, uniformBlockIndex, 0);

		uniformBuffer = std::make_shared<GlBuffer>(BufferType::Uniform,
			sizeof(UniformBufferObject), GL_DYNAMIC_DRAW, nullptr);
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBuffer->getBuffer());

        auto textureLocation = getUniformLocation(program, "u_Texture");

        GlPipeline::bind();
        glUniform1i(textureLocation, 0);
    }
    GlTexDiffusePipeline::~GlTexDiffusePipeline()
    {}

    std::shared_ptr<Texture> GlTexDiffusePipeline::getTexture() const
    {
        return texture;
    }

    const Vector4& GlTexDiffusePipeline::getObjectColor() const
    {
        return ubo.objectColor;
    }
	void GlTexDiffusePipeline::setObjectColor(const Vector4& color)
    {
        ubo.objectColor = Vector4(color);
    }

    const Vector4& GlTexDiffusePipeline::getAmbientColor() const
    {
        return ubo.ambientColor;
    }
	void GlTexDiffusePipeline::setAmbientColor(const Vector4& color)
    {
        ubo.ambientColor = Vector4(color);
    }

	const Vector4& GlTexDiffusePipeline::getLightColor() const
    {
        return ubo.lightColor;
    }
	void GlTexDiffusePipeline::setLightColor(const Vector4& color)
    {
        ubo.lightColor = Vector4(color);
    }

	const Vector3& GlTexDiffusePipeline::getLightDirection() const
    {
        return ubo.lightDirection;
    }
	void GlTexDiffusePipeline::setLightDirection(const Vector3& direction)
    {
        ubo.lightDirection = direction.getNormalized();
    }

    const Vector2& GlTexDiffusePipeline::getTextureScale() const
    {
        return ubo.textureScale;
    }
	void GlTexDiffusePipeline::setTextureScale(const Vector2& scale)
    {
        ubo.textureScale = Vector2(scale);
    }

    const Vector2& GlTexDiffusePipeline::getTextureOffset() const
    {
        return ubo.textureOffset;
    }
	void GlTexDiffusePipeline::setTextureOffset(const Vector2& offset)
    {
        ubo.textureOffset = Vector2(offset);
    }

	void GlTexDiffusePipeline::bind()
    {
        GlPipeline::bind();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glDisable(GL_STENCIL_TEST);
		glDisable(GL_BLEND);
		glCullFace(GL_BACK); 
		glFrontFace(GL_CW);

        glActiveTexture(GL_TEXTURE0);
        texture->bind();
    }
    void GlTexDiffusePipeline::flush()
    {
        uniformBuffer->setData(&ubo, sizeof(UniformBufferObject));
    }
    void GlTexDiffusePipeline::setAttributes()
    {
        glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        setVertexAttributePointer(0, 3, GL_FLOAT, GL_FALSE,
            sizeof(Vector3) * 2 + sizeof(Vector2));
		setVertexAttributePointer(1, 3, GL_FLOAT, GL_FALSE,
            sizeof(Vector3) * 2 + sizeof(Vector2), sizeof(Vector3));
        setVertexAttributePointer(2, 2, GL_FLOAT, GL_FALSE,
            sizeof(Vector3) * 2 + sizeof(Vector2), sizeof(Vector3) * 2);
    }

    void GlTexDiffusePipeline::setUniforms(
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
