#include "Injector/Graphics/OpenGL/Pipeline/GlImageDiffuseGpuPipeline.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	GlImageDiffuseGpuPipeline::GlImageDiffuseGpuPipeline(
		const std::shared_ptr<GlGpuShader>& vertexShader,
		const std::shared_ptr<GlGpuShader>& fragmentShader,
		const std::shared_ptr<GlGpuImage>& _image,
		const UniformBufferObject& _ubo) :
		GlGpuPipeline(GL_TRIANGLES),
		ubo(_ubo),
		image(_image)
	{
		if (!vertexShader)
		{
			throw NullException(
				"GlImageDiffuseGpuPipeline",
				"GlImageDiffuseGpuPipeline",
				"vertexShader");
		}
		if (!fragmentShader)
		{
			throw NullException(
				"GlImageDiffuseGpuPipeline",
				"GlImageDiffuseGpuPipeline",
				"fragmentShader");
		}
		if (!_image)
		{
			throw NullException(
				"GlImageDiffuseGpuPipeline",
				"GlImageDiffuseGpuPipeline",
				"image");
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
				"GlImageDiffuseGpuPipeline",
				"GlImageDiffuseGpuPipeline",
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

		auto imageLocation = getUniformLocation(
			program,
			"u_Image");

		GlGpuPipeline::bind();
		glUniform1i(imageLocation, 0);
	}

	std::shared_ptr<GpuImage> GlImageDiffuseGpuPipeline::getImage() const
	{
		return image;
	}

	const Vector4& GlImageDiffuseGpuPipeline::getObjectColor() const
	{
		return ubo.objectColor;
	}
	void GlImageDiffuseGpuPipeline::setObjectColor(const Vector4& color)
	{
		ubo.objectColor = Vector4(color);
	}

	const Vector4& GlImageDiffuseGpuPipeline::getAmbientColor() const
	{
		return ubo.ambientColor;
	}
	void GlImageDiffuseGpuPipeline::setAmbientColor(const Vector4& color)
	{
		ubo.ambientColor = Vector4(color);
	}

	const Vector4& GlImageDiffuseGpuPipeline::getLightColor() const
	{
		return ubo.lightColor;
	}
	void GlImageDiffuseGpuPipeline::setLightColor(const Vector4& color)
	{
		ubo.lightColor = Vector4(color);
	}

	const Vector3& GlImageDiffuseGpuPipeline::getLightDirection() const
	{
		return ubo.lightDirection;
	}
	void GlImageDiffuseGpuPipeline::setLightDirection(const Vector3& direction)
	{
		ubo.lightDirection = direction.getNormalized();
	}

	const Vector2& GlImageDiffuseGpuPipeline::getImageScale() const
	{
		return ubo.imageScale;
	}
	void GlImageDiffuseGpuPipeline::setTextureScale(const Vector2& scale)
	{
		ubo.imageScale = Vector2(scale);
	}

	const Vector2& GlImageDiffuseGpuPipeline::getImageOffset() const
	{
		return ubo.imageOffset;
	}
	void GlImageDiffuseGpuPipeline::setTextureOffset(const Vector2& offset)
	{
		ubo.imageOffset = Vector2(offset);
	}

	void GlImageDiffuseGpuPipeline::bind()
	{
		GlGpuPipeline::bind();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glDisable(GL_STENCIL_TEST);
		glDisable(GL_BLEND);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);

		glActiveTexture(GL_TEXTURE0);
		image->bind();

		glBindBufferBase(
			GL_UNIFORM_BUFFER,
			0,
			uniformBuffer->getBuffer());
	}
	void GlImageDiffuseGpuPipeline::flush()
	{
		uniformBuffer->setData(
			&ubo,
			sizeof(UniformBufferObject));
	}
	void GlImageDiffuseGpuPipeline::setAttributes()
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

	void GlImageDiffuseGpuPipeline::setUniforms(
		const Matrix4& model,
		const Matrix4& view,
		const Matrix4& proj,
		const Matrix4& viewProj,
		const Matrix4& mvp)
	{
		setUniform(
			mvpLocation,
			mvp);
		setUniform(
			normalLocation,
			model.getInverted().getMatrix3(),
			GL_TRUE);
	}
}
