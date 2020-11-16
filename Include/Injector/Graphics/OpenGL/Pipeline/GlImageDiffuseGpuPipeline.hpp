#pragma once
#include "Injector/Graphics/OpenGL/Pipeline/GlDiffuseGpuPipeline.hpp"
#include "Injector/Graphics/Pipeline/ImageDiffuseGpuPipeline.hpp"
#include "Injector/Graphics/OpenGL/GlGpuImage.hpp"
#include "Injector/Graphics/OpenGL/GlGpuShader.hpp"

namespace Injector
{
	class GlImageDiffuseGpuPipeline :
		public GlGpuPipeline,
		public ImageDiffuseGpuPipeline
	{
	 public:
		struct UniformBufferObject
		{
			FloatVector4 objectColor;
			FloatVector4 ambientColor;
			FloatVector4 lightColor;
			FloatVector3 lightDirection;
			float alignment;
			FloatVector2 imageScale;
			FloatVector2 imageOffset;

			explicit UniformBufferObject(
				const FloatVector4& _objectColor,
				const FloatVector4& _ambientColor,
				const FloatVector4& _lightColor,
				const FloatVector3& _lightDirection,
				const FloatVector2& _imageScale,
				const FloatVector2& _imageOffset) :
				objectColor(_objectColor),
				ambientColor(_ambientColor),
				lightColor(_lightColor),
				lightDirection(_lightDirection),
				alignment(),
				imageScale(_imageScale),
				imageOffset(_imageOffset)
			{
			}
		};
	 protected:
		GLint mvpLocation;
		GLint normalLocation;
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

		std::shared_ptr<GlGpuBuffer> uniformBuffer;
		std::shared_ptr<GlGpuImage> image;

		UniformBufferObject ubo;
	 public:
		GlImageDiffuseGpuPipeline(
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
			const UniformBufferObject& ubo);

		GpuImageFilter getImageMinFilter() const override;
		GpuImageFilter getImageMagFilter() const override;
		GpuImageFilter getMipmapFilter() const override;

		GpuImageWrap getImageWrapU() const override;
		GpuImageWrap getImageWrapV() const override;
		GpuImageWrap getImageWrapW() const override;

		std::shared_ptr<GpuImage> getImage() const override;

		const FloatVector4& getObjectColor() const override;
		void setObjectColor(const FloatVector4& color) override;

		const FloatVector4& getAmbientColor() const override;
		void setAmbientColor(const FloatVector4& color) override;

		const FloatVector4& getLightColor() const override;
		void setLightColor(const FloatVector4& color) override;

		const FloatVector3& getLightDirection() const override;
		void setLightDirection(const FloatVector3& direction) override;

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
