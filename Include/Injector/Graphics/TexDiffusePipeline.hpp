#pragma once
#include "Injector/Graphics/DiffusePipeline.hpp"
#include "Injector/Graphics/Texture.hpp"

#include <memory>

namespace Injector
{
	class TexDiffusePipeline : public DiffusePipeline
	{
	public:
		virtual ~TexDiffusePipeline();

		virtual std::shared_ptr<Texture> getTexture() const;

		virtual const Vector2& getTextureScale() const;
		virtual void setTextureScale(const Vector2& scale);

        virtual const Vector2& getTextureOffset() const;
		virtual void setTextureOffset(const Vector2& offset);
	};
}
