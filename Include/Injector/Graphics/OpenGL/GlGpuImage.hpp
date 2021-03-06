#pragma once
#include "Injector/Graphics/GpuImage.hpp"
#include "Injector/Graphics/ImageData.hpp"
#include "Injector/GlfwDefines.hpp"

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
			GpuImageFormat format,
			const SizeVector3& size,
			bool useMipmap,
			const void* data = nullptr);
		~GlGpuImage() override;

		GLuint getTexture() const noexcept;
		GLenum getGlType() const noexcept;

		void bind() noexcept;
		void unbind() noexcept;
	};
}
