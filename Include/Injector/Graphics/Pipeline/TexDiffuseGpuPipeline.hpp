#pragma once
#include "Injector/Graphics/Pipeline/DiffuseGpuPipeline.hpp"
#include "Injector/Graphics/GpuImage.hpp"

#include <memory>

namespace Injector
{
	class TexDiffuseGpuPipeline : public DiffuseGpuPipeline
	{
	public:
		virtual ~TexDiffuseGpuPipeline();

		virtual std::shared_ptr<GpuImage> getTexture() const;

		virtual const Vector2& getTextureScale() const;
		virtual void setTextureScale(const Vector2& scale);

        virtual const Vector2& getTextureOffset() const;
		virtual void setTextureOffset(const Vector2& offset);
	};
}
