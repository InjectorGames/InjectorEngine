#pragma once
#include "Injector/Graphics/Pipeline/DiffuseGpuPipeline.hpp"
#include "Injector/Graphics/GpuImage.hpp"

#include <memory>

namespace Injector
{
	class ImageDiffuseGpuPipeline : public DiffuseGpuPipeline
	{
	 public:
		virtual std::shared_ptr<GpuImage> getImage() const = 0;

		virtual const Vector2& getImageScale() const = 0;
		virtual void setImageScale(const Vector2& scale) = 0;

		virtual const Vector2& getImageOffset() const = 0;
		virtual void setImageOffset(const Vector2& offset) = 0;
	};
}
