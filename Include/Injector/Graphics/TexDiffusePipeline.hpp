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
	};
}
