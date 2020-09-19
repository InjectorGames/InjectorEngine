#include "Injector/Graphics/Pipeline/GlTexDiffuseGpuPipeline.hpp"
#include "Injector/Storage/FileStream.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	GlTexDiffuseGpuPipeline::GlTexDiffuseGpuPipeline(
		const std::shared_ptr<GlGpuShader>& vertexShader,
		const std::shared_ptr<GlGpuShader>& fragmentShader,
		const std::shared_ptr<GlGpuImage>& _texture,
		const Vector4& objectColor,
		const Vector4& ambientColor,
		const Vector4& lightColor,
		const Vector3& lightDirection,
		const Vector2& textureScale,
		const Vector2& textureOffset) :
		GlGpuPipeline(GL_TRIANGLES),
		ubo(objectColor, ambientColor, lightColor,
			lightDirection.getNormalized(),
			textureScale, textureOffset),
		texture(_texture)
	{
		if (!vertexShader || !fragmentShader || !_texture)
			throw NullException("GlTexDiffuseGpuPipeline", "GlTexDiffuseGpuPipeline", "shader/texture");

		glAttachShader(program, vertexShader->getShader());
		glAttachShader(program, fragmentShader->getShader());
		glLinkProgram(program);
		glDetachShader(program, vertexShader->getShader());
		glDetachShader(program, fragmentShader->getShader());

		if (!getLinkStatus(program))
		{
			auto log = getInfoLog(program);
			glDeleteProgram(program);

			throw Exception("GlTexDiffuseGpuPipeline", "GlTexDiffuseGpuPipeline",
				"Failed to link program, " + log);
		}

		mvpLocation = getUniformLocation(program, "u_MVP");
		normalLocation = getUniformLocation(program, "u_Normal");

		auto uniformBlockIndex = getUniformBlockIndex(program, "FragmentBufferObject");
		glUniformBlockBinding(program, uniformBlockIndex, 0);

		uniformBuffer = std::make_shared<GlGpuBuffer>(GpuBufferType::Uniform,
			sizeof(UniformBufferObject), GL_DYNAMIC_DRAW, nullptr);

		auto textureLocation = getUniformLocation(program, "u_Texture");

		GlGpuPipeline::bind();
		glUniform1i(textureLocation, 0);
	}
	GlTexDiffuseGpuPipeline::~GlTexDiffuseGpuPipeline()
	{
	}

	std::shared_ptr<GpuImage> GlTexDiffuseGpuPipeline::getTexture() const
	{
		return texture;
	}

	const Vector4& GlTexDiffuseGpuPipeline::getObjectColor() const
	{
		return ubo.objectColor;
	}
	void GlTexDiffuseGpuPipeline::setObjectColor(const Vector4& color)
	{
		ubo.objectColor = Vector4(color);
	}

	const Vector4& GlTexDiffuseGpuPipeline::getAmbientColor() const
	{
		return ubo.ambientColor;
	}
	void GlTexDiffuseGpuPipeline::setAmbientColor(const Vector4& color)
	{
		ubo.ambientColor = Vector4(color);
	}

	const Vector4& GlTexDiffuseGpuPipeline::getLightColor() const
	{
		return ubo.lightColor;
	}
	void GlTexDiffuseGpuPipeline::setLightColor(const Vector4& color)
	{
		ubo.lightColor = Vector4(color);
	}

	const Vector3& GlTexDiffuseGpuPipeline::getLightDirection() const
	{
		return ubo.lightDirection;
	}
	void GlTexDiffuseGpuPipeline::setLightDirection(const Vector3& direction)
	{
		ubo.lightDirection = direction.getNormalized();
	}

	const Vector2& GlTexDiffuseGpuPipeline::getTextureScale() const
	{
		return ubo.textureScale;
	}
	void GlTexDiffuseGpuPipeline::setTextureScale(const Vector2& scale)
	{
		ubo.textureScale = Vector2(scale);
	}

	const Vector2& GlTexDiffuseGpuPipeline::getTextureOffset() const
	{
		return ubo.textureOffset;
	}
	void GlTexDiffuseGpuPipeline::setTextureOffset(const Vector2& offset)
	{
		ubo.textureOffset = Vector2(offset);
	}

	void GlTexDiffuseGpuPipeline::bind()
	{
		GlGpuPipeline::bind();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glDisable(GL_STENCIL_TEST);
		glDisable(GL_BLEND);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);

		glActiveTexture(GL_TEXTURE0);
		texture->bind();

		glBindBufferBase(GL_UNIFORM_BUFFER, 0,
			uniformBuffer->getBuffer());
	}
	void GlTexDiffuseGpuPipeline::flush()
	{
		uniformBuffer->setData(&ubo, sizeof(UniformBufferObject));
	}
	void GlTexDiffuseGpuPipeline::setAttributes()
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

	void GlTexDiffuseGpuPipeline::setUniforms(
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
