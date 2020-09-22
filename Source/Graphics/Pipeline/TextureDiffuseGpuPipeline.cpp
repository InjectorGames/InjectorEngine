#include "Injector/Graphics/Pipeline/TextureDiffuseGpuPipeline.hpp"
#include "Injector/Exception/NotImplementedException.hpp"

namespace Injector
{
	TextureDiffuseGpuPipeline::~TextureDiffuseGpuPipeline()
	{
	}

	std::shared_ptr<GpuImage> TextureDiffuseGpuPipeline::getTexture() const
	{
		throw NotImplementedException(
			"TextureDiffuseGpuPipeline",
			"getTexture");
	}

	const Vector2& TextureDiffuseGpuPipeline::getTextureScale() const
	{
		throw NotImplementedException(
			"TextureDiffuseGpuPipeline",
			"getTextureScale");
	}
	void TextureDiffuseGpuPipeline::setTextureScale(const Vector2& scale)
	{
		throw NotImplementedException(
			"TextureDiffuseGpuPipeline",
			"setTextureScale");
	}

	const Vector2& TextureDiffuseGpuPipeline::getTextureOffset() const
	{
		throw NotImplementedException(
			"TextureDiffuseGpuPipeline",
			"getTextureOffset");
	}
	void TextureDiffuseGpuPipeline::setTextureOffset(const Vector2& offset)
	{
		throw NotImplementedException(
			"TextureDiffuseGpuPipeline",
			"setTextureOffset");
	}
}
