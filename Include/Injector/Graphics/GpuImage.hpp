#pragma once
#include "Injector/Graphics/GpuImageType.hpp"
#include "Injector/Graphics/GpuImageFormat.hpp"
#include "Injector/Mathematics/Vector3.hpp"

namespace Injector
{
	class GpuImage
	{
	 protected:
		GpuImageType type;
		GpuImageFormat format;
		IntVector3 size;

		bool useMipmap;
	 public:
		GpuImage(
			GpuImageType type,
			GpuImageFormat format,
			const IntVector3& size,
			bool useMipmap);
		GpuImage(GpuImage&& image) = delete;
		GpuImage(const GpuImage& image) = delete;
		virtual ~GpuImage() = default;

		GpuImageType getType() const noexcept;
		GpuImageFormat getFormat() const noexcept;
		const IntVector3& getSize() const noexcept;

		bool isUseMipmap() const noexcept;
	};
}
