#include "Injector/Graphics/OpenGL/Pipeline/GlTextureDiffuseGpuPipeline.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	GlTextureDiffuseGpuPipeline::GlTextureDiffuseGpuPipeline(
		const std::shared_ptr<GlGpuShader>& vertexShader,
		const std::shared_ptr<GlGpuShader>& fragmentShader,
		const std::shared_ptr<GlGpuImage>& _texture,
		const UniformBufferObject& _ubo) :
		GlGpuPipeline(GL_TRIANGLES),
		ubo(_ubo),
		texture(_texture)
	{
		if (!vertexShader || !fragmentShader || !_texture)
		{
			throw NullException(
				"GlTextureDiffuseGpuPipeline",
				"GlTextureDiffuseGpuPipeline",
				"shader/texture");
		}

		glAttachShader(program, vertexShader->getShader());
		glAttachShader(program, fragmentShader->getShader());
		glLinkProgram(program);
		glDetachShader(program, vertexShader->getShader());
		glDetachShader(program, fragmentShader->getShader());

		if (!getLinkStatus(program))
		{
			auto log = getInfoLog(program);
			glDeleteProgram(program);

			throw Exception(
				"GlTextureDiffuseGpuPipeline",
				"GlTextureDiffuseGpuPipeline",
				"Failed to link program, " + log);
		}

		mvpLocation = getUniformLocation(
			program, "u_MVP");
		normalLocation = getUniformLocation(
			program, "u_Normal");

		auto uniformBlockIndex = getUniformBlockIndex(
			program, "FragmentBufferObject");
		glUniformBlockBinding(program, uniformBlockIndex, 0);

		uniformBuffer = std::make_shared<GlGpuBuffer>(
			GpuBufferType::Uniform,
			sizeof(UniformBufferObject),
			GL_DYNAMIC_DRAW,
			nullptr);

		auto textureLocation = getUniformLocation(
			program, "u_Texture");

		GlGpuPipeline::bind();
		glUniform1i(textureLocation, 0);
	}

	std::shared_ptr<GpuImage> GlTextureDiffuseGpuPipeline::getTexture() const
	{
		return texture;
	}

	const Vector4& GlTextureDiffuseGpuPipeline::getObjectColor() const
	{
		return ubo.objectColor;
	}
	void GlTextureDiffuseGpuPipeline::setObjectColor(const Vector4& color)
	{
		ubo.objectColor = Vector4(color);
	}

	const Vector4& GlTextureDiffuseGpuPipeline::getAmbientColor() const
	{
		return ubo.ambientColor;
	}
	void GlTextureDiffuseGpuPipeline::setAmbientColor(const Vector4& color)
	{
		ubo.ambientColor = Vector4(color);
	}

	const Vector4& GlTextureDiffuseGpuPipeline::getLightColor() const
	{
		return ubo.lightColor;
	}
	void GlTextureDiffuseGpuPipeline::setLightColor(const Vector4& color)
	{
		ubo.lightColor = Vector4(color);
	}

	const Vector3& GlTextureDiffuseGpuPipeline::getLightDirection() const
	{
		return ubo.lightDirection;
	}
	void GlTextureDiffuseGpuPipeline::setLightDirection(const Vector3& direction)
	{
		ubo.lightDirection = direction.getNormalized();
	}

	const Vector2& GlTextureDiffuseGpuPipeline::getTextureScale() const
	{
		return ubo.textureScale;
	}
	void GlTextureDiffuseGpuPipeline::setTextureScale(const Vector2& scale)
	{
		ubo.textureScale = Vector2(scale);
	}

	const Vector2& GlTextureDiffuseGpuPipeline::getTextureOffset() const
	{
		return ubo.textureOffset;
	}
	void GlTextureDiffuseGpuPipeline::setTextureOffset(const Vector2& offset)
	{
		ubo.textureOffset = Vector2(offset);
	}

	void GlTextureDiffuseGpuPipeline::bind()
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
	void GlTextureDiffuseGpuPipeline::flush()
	{
		uniformBuffer->setData(&ubo, sizeof(UniformBufferObject));
	}
	void GlTextureDiffuseGpuPipeline::setAttributes()
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		setVertexAttributePointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vector3) * 2 + sizeof(Vector2),
			0);
		setVertexAttributePointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vector3) * 2 + sizeof(Vector2),
			sizeof(Vector3));
		setVertexAttributePointer(
			2, 2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vector3) * 2 + sizeof(Vector2),
			sizeof(Vector3) * 2);
	}

	void GlTextureDiffuseGpuPipeline::setUniforms(
		const Matrix4& model,
		const Matrix4& view,
		const Matrix4& proj,
		const Matrix4& viewProj,
		const Matrix4& mvp)
	{
		setUniform(mvpLocation, mvp);
		setUniform(normalLocation,
			model.getInverted().getMatrix3(), GL_TRUE);
	}
}
