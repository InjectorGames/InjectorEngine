#pragma once
#include "Injector/Graphics/Pipeline/DiffuseGpuPipeline.hpp"
#include "Injector/Graphics/GpuImage.hpp"

#include <memory>

namespace Injector
{
	class TextureDiffuseGpuPipeline : public DiffuseGpuPipeline
	{
	 public:
		virtual std::shared_ptr<GpuImage> getTexture() const = 0;

		virtual const Vector2& getTextureScale() const = 0;
		virtual void setTextureScale(const Vector2& scale) = 0;

		virtual const Vector2& getTextureOffset() const = 0;
		virtual void setTextureOffset(const Vector2& offset) = 0;
	};
}
