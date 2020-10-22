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
			Vector4 objectColor;
			Vector4 ambientColor;
			Vector4 lightColor;
			Vector3 lightDirection;
			float alignment;
			Vector2 imageScale;
			Vector2 imageOffset;

			explicit UniformBufferObject(
				const Vector4& _objectColor,
				const Vector4& _ambientColor,
				const Vector4& _lightColor,
				const Vector3& _lightDirection,
				const Vector2& _imageScale,
				const Vector2& _imageOffset) :
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

		const Vector4& getObjectColor() const override;
		void setObjectColor(const Vector4& color) override;

		const Vector4& getAmbientColor() const override;
		void setAmbientColor(const Vector4& color) override;

		const Vector4& getLightColor() const override;
		void setLightColor(const Vector4& color) override;

		const Vector3& getLightDirection() const override;
		void setLightDirection(const Vector3& direction) override;

		const Vector2& getImageScale() const override;
		void setImageScale(const Vector2& scale) override;

		const Vector2& getImageOffset() const override;
		void setImageOffset(const Vector2& offset) override;

		void bind() override;
		void flush() override;
		void setAttributes() override;

		void setUniforms(
			const Matrix4& model,
			const Matrix4& view,
			const Matrix4& proj,
			const Matrix4& viewProj,
			const Matrix4& mvp) override;
	};
}
