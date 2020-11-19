#pragma once
#include "Injector/Graphics/OpenGL/GlGpuPipeline.hpp"
#include "Injector/Graphics/Pipeline/ImageGpuPipeline.hpp"
#include "Injector/Graphics/OpenGL/GlGpuImage.hpp"
#include "Injector/Graphics/OpenGL/GlGpuShader.hpp"

namespace Injector
{
	class GlGuiGpuPipeline :
		public GlGpuPipeline,
		public ImageGpuPipeline
	{
	 protected:
		GLint projLocation;
		GLint imageScaleLocation;
		GLint imageOffsetLocation;
		GLint imageLocation;

		GLint glImageMinFilter;
		GLint glImageMagFilter;
		GLint glImageWrapU;
		GLint glImageWrapV;
		GLint glImageWrapW;

		GpuImageFilter imageMinFilter;
		GpuImageFilter imageMagFilter;
		GpuImageFilter mipmapFilter;
		GpuImageWrap imageWrapU;
		GpuImageWrap imageWrapV;
		GpuImageWrap imageWrapW;

		FloatVector2 imageScale;
		FloatVector2 imageOffset;

		std::shared_ptr<GlGpuImage> image;
	 public:
		GlGuiGpuPipeline(
			GpuDrawMode drawMode,
			GpuImageFilter imageMinFilter,
			GpuImageFilter imageMagFilter,
			GpuImageFilter mipmapFilter,
			GpuImageWrap imageWrapU,
			GpuImageWrap imageWrapV,
			GpuImageWrap imageWrapW,
			const std::shared_ptr<GlGpuShader>& vertexShader,
			const std::shared_ptr<GlGpuShader>& fragmentShader,
			const std::shared_ptr<GlGpuImage>& image,
			const FloatVector2& imageScale,
			const FloatVector2& imageOffset);

		GpuImageFilter getImageMinFilter() const override;
		GpuImageFilter getImageMagFilter() const override;
		GpuImageFilter getMipmapFilter() const override;

		GpuImageWrap getImageWrapU() const override;
		GpuImageWrap getImageWrapV() const override;
		GpuImageWrap getImageWrapW() const override;

		std::shared_ptr<GpuImage> getImage() const override;

		const FloatVector2& getImageScale() const override;
		void setImageScale(const FloatVector2& scale) override;

		const FloatVector2& getImageOffset() const override;
		void setImageOffset(const FloatVector2& offset) override;

		void bind() override;
		void flush() override;
		void setAttributes() override;

		void setUniforms(
			const FloatMatrix4& model,
			const FloatMatrix4& view,
			const FloatMatrix4& proj,
			const FloatMatrix4& viewProj,
			const FloatMatrix4& mvp) override;
	};
}
