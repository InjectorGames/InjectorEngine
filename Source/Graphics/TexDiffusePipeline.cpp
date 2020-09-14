#include "Injector/Graphics/TexDiffusePipeline.hpp"
#include "Injector/Exception/NotImplementedException.hpp"

namespace Injector
{
    TexDiffusePipeline::~TexDiffusePipeline()
    {}

	std::shared_ptr<Texture> TexDiffusePipeline::getTexture() const
    {
        throw NotImplementedException("TexDiffusePipeline", "getTexture");
    }

    const Vector2& TexDiffusePipeline::getTextureScale() const
    {
        throw NotImplementedException("TexDiffusePipeline", "getTextureScale");
    }
    void TexDiffusePipeline::setTextureScale(const Vector2& textureScale)
    {
        throw NotImplementedException("TexDiffusePipeline", "setTextureScale");
    }

    const Vector2& TexDiffusePipeline::getTextureOffset() const
    {
        throw NotImplementedException("TexDiffusePipeline", "getTextureOffset");
    }
	void TexDiffusePipeline::setTextureOffset(const Vector2& textureOffset)
    {
        throw NotImplementedException("TexDiffusePipeline", "setTextureOffset");
    }
}
