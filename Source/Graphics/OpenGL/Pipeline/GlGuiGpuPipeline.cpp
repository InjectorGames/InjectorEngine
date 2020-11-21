#include "Injector/Graphics/OpenGL/Pipeline/GlGuiGpuPipeline.hpp"
#include "Injector/Exception/NullException.hpp"
#include "Injector/Graphics/ImguiDefines.hpp"
#include "Injector/Graphics/OpenGL/GlGpuImageWrap.hpp"
#include "Injector/Graphics/OpenGL/GlGpuImageFilter.hpp"

namespace Injector
{
	GlGuiGpuPipeline::GlGuiGpuPipeline(
		GpuDrawMode drawMode,
		GpuImageFilter _imageMinFilter,
		GpuImageFilter _imageMagFilter,
		GpuImageFilter _mipmapFilter,
		GpuImageWrap _imageWrapU,
		GpuImageWrap _imageWrapV,
		GpuImageWrap _imageWrapW,
		const std::shared_ptr<GlGpuShader>& vertexShader,
		const std::shared_ptr<GlGpuShader>& fragmentShader,
		const std::shared_ptr<GlGpuImage>& _image,
		const FloatVector2& _imageScale,
		const FloatVector2& _imageOffset) :
		GlGpuPipeline(drawMode),
		imageMinFilter(_imageMinFilter),
		imageMagFilter(_imageMagFilter),
		mipmapFilter(_mipmapFilter),
		imageWrapU(_imageWrapU),
		imageWrapV(_imageWrapV),
		imageWrapW(_imageWrapW),
		imageScale(_imageScale),
		imageOffset(_imageOffset),
		image(_image)
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
		if (!_image)
		{
			throw NullException(
				THIS_FUNCTION_NAME,
				"image");
		}

		glImageMinFilter = toGlGpuImageFilter(
			_imageMinFilter,
			_image->isUseMipmap(),
			_mipmapFilter);
		glImageMagFilter = toGlGpuImageFilter(
			_imageMagFilter,
			false,
			_mipmapFilter);

		glImageWrapU = toGlGpuImageWrap(_imageWrapU);
		glImageWrapV = toGlGpuImageWrap(_imageWrapV);
		glImageWrapW = toGlGpuImageWrap(_imageWrapW);

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
		imageScaleLocation = getUniformLocation(
			program,
			"u_ImageScale");
		imageOffsetLocation = getUniformLocation(
			program,
			"u_ImageOffset");
		imageLocation = getUniformLocation(
			program,
			"u_Image");

		GlGpuPipeline::bind();
		glUniform1i(imageLocation, 0);
	}

	GpuImageFilter GlGuiGpuPipeline::getImageMinFilter() const
	{
		return imageMinFilter;
	}
	GpuImageFilter GlGuiGpuPipeline::getImageMagFilter() const
	{
		return imageMagFilter;
	}
	GpuImageFilter GlGuiGpuPipeline::getMipmapFilter() const
	{
		return mipmapFilter;
	}

	GpuImageWrap GlGuiGpuPipeline::getImageWrapU() const
	{
		return imageWrapU;
	}
	GpuImageWrap GlGuiGpuPipeline::getImageWrapV() const
	{
		return imageWrapV;
	}
	GpuImageWrap GlGuiGpuPipeline::getImageWrapW() const
	{
		return imageWrapW;
	}

	const FloatVector2& GlGuiGpuPipeline::getImageScale() const
	{
		return imageScale;
	}
	void GlGuiGpuPipeline::setImageScale(const FloatVector2& scale)
	{
		imageScale = FloatVector2(scale);
	}

	const FloatVector2& GlGuiGpuPipeline::getImageOffset() const
	{
		return imageOffset;
	}
	void GlGuiGpuPipeline::setImageOffset(const FloatVector2& offset)
	{
		imageOffset = FloatVector2(offset);
	}

	std::shared_ptr<GpuImage> GlGuiGpuPipeline::getImage() const
	{
		return image;
	}

	void GlGuiGpuPipeline::bind()
	{
		GlGpuPipeline::bind();
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glDisable(GL_SCISSOR_TEST);
		glDisable(GL_STENCIL_TEST);

		// TODO: fix no rendering with blending
		/*glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(
			GL_SRC_ALPHA,
			GL_ONE_MINUS_SRC_ALPHA);*/


		glActiveTexture(GL_TEXTURE0);
		image->bind();

		auto imageType = image->getGlType();

		glTexParameteri(
			imageType,
			GL_TEXTURE_MIN_FILTER,
			glImageMinFilter);
		glTexParameteri(
			imageType,
			GL_TEXTURE_MAG_FILTER,
			glImageMagFilter);

		glTexParameteri(
			imageType,
			GL_TEXTURE_WRAP_S,
			glImageWrapU);
		glTexParameteri(
			imageType,
			GL_TEXTURE_WRAP_T,
			glImageWrapV);
		glTexParameteri(
			imageType,
			GL_TEXTURE_WRAP_R,
			glImageWrapW);
	}
	void GlGuiGpuPipeline::flush()
	{
		GlGpuPipeline::bind();

		setUniform(
			imageScaleLocation,
			imageScale);
		setUniform(
			imageOffsetLocation,
			imageOffset);
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
			sizeof(ImDrawVert),
			IM_OFFSETOF(ImDrawVert, pos));
		setVertexAttributePointer(
			1,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(ImDrawVert),
			IM_OFFSETOF(ImDrawVert, uv));
		setVertexAttributePointer(
			2,
			4,
			GL_UNSIGNED_BYTE,
			GL_TRUE,
			sizeof(ImDrawVert),
			IM_OFFSETOF(ImDrawVert, col));
	}

	void GlGuiGpuPipeline::setUniforms(
		const FloatMatrix4& model,
		const FloatMatrix4& view,
		const FloatMatrix4& proj,
		const FloatMatrix4& viewProj,
		const FloatMatrix4& mvp)
	{
		setUniform(
			projLocation,
			proj);
	}
}
