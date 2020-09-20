#include "Injector/Graphics/Pipeline/TexDiffuseGpuPipeline.hpp"
#include "Injector/Exception/NotImplementedException.hpp"

namespace Injector
{
	TexDiffuseGpuPipeline::~TexDiffuseGpuPipeline()
	{
	}

	std::shared_ptr<GpuImage> TexDiffuseGpuPipeline::getTexture() const
	{
		throw NotImplementedException(
			"TexDiffuseGpuPipeline",
			"getTexture");
	}

	const Vector2& TexDiffuseGpuPipeline::getTextureScale() const
	{
		throw NotImplementedException(
			"TexDiffuseGpuPipeline",
			"getTextureScale");
	}
	void TexDiffuseGpuPipeline::setTextureScale(const Vector2& scale)
	{
		throw NotImplementedException(
			"TexDiffuseGpuPipeline",
			"setTextureScale");
	}

	const Vector2& TexDiffuseGpuPipeline::getTextureOffset() const
	{
		throw NotImplementedException(
			"TexDiffuseGpuPipeline",
			"getTextureOffset");
	}
	void TexDiffuseGpuPipeline::setTextureOffset(const Vector2& offset)
	{
		throw NotImplementedException(
			"TexDiffuseGpuPipeline",
			"setTextureOffset");
	}
}
