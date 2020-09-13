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
}
