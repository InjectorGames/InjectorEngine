#pragma once
#include "Injector/Graphics/GpuImage.hpp"
#include "Injector/Graphics/GpuImageWrap.hpp"
#include "Injector/Graphics/GpuImageFilter.hpp"

#include <memory>

namespace Injector
{
	class ImageGpuPipeline
	{
		virtual GpuImageFilter getImageMinFilter() const = 0;
		virtual GpuImageFilter getImageMagFilter() const = 0;
		virtual GpuImageFilter getMipmapFilter() const = 0;

		virtual GpuImageWrap getImageWrapU() const = 0;
		virtual GpuImageWrap getImageWrapV() const = 0;
		virtual GpuImageWrap getImageWrapW() const = 0;

		virtual std::shared_ptr<GpuImage> getImage() const = 0;

		virtual const FloatVector2& getImageScale() const = 0;
		virtual void setImageScale(const FloatVector2& scale) = 0;

		virtual const FloatVector2& getImageOffset() const = 0;
		virtual void setImageOffset(const FloatVector2& offset) = 0;
	};
}
