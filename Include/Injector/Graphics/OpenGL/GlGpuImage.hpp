#pragma once
#include "Injector/Graphics/GpuImage.hpp"
#include "Injector/Graphics/ImageData.hpp"
#include "Injector/Graphics/GlfwDefines.hpp"

namespace Injector
{
	class GlGpuImage : public GpuImage
	{
	 protected:
		GLuint texture;
		GLenum glType;
	 public:
		GlGpuImage(
			GpuImageType type,
			const IntVector3& size,
			GpuImageFormat format,
			GpuImageFilter minFilter,
			GpuImageFilter magFilter,
			GpuImageWrap wrapU,
			GpuImageWrap wrapV,
			GpuImageWrap wrapW,
			bool useMipmap,
			const std::shared_ptr<ImageData>& data = nullptr);
		~GlGpuImage() override;

		GLuint getTexture() const noexcept;
		GLenum getGlType() const noexcept;

		void bind() noexcept;
		void unbind() noexcept;

		static GLenum toGlType(GpuImageType type);
		static GLenum toGlFormat(GpuImageFormat format);
		static GLint toGlFilter(GpuImageFilter filter, bool useMipmap);
		static GLint toGlWrap(GpuImageWrap wrap);
	};
}
