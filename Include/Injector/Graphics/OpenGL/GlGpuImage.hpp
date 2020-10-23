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
			GpuImageFormat format,
			const IntVector3& size,
			bool useMipmap,
			const std::shared_ptr<ImageData>& data = nullptr);
		~GlGpuImage() override;

		GLuint getTexture() const noexcept;
		GLenum getGlType() const noexcept;

		void bind() noexcept;
		void unbind() noexcept;
	};
}
