#pragma once
#include "Injector/Graphics/GlDiffusePipeline.hpp"
#include "Injector/Graphics/TexDiffusePipeline.hpp"
#include "Injector/Graphics/GlTexture.hpp"

namespace Injector
{
    class GlTexDiffusePipeline : public GlDiffusePipeline, public TexDiffusePipeline
    {
    protected:
        GLint textureLocation;
        std::shared_ptr<GlTexture> texture;
    public:
        GlTexDiffusePipeline(bool gles,
            const std::shared_ptr<GlTexture>& texture,
            const Vector4& objectColor = Vector4::one,
			const Vector4& ambientColor = Vector4::one / 2,
			const Vector4& lightColor = Vector4::one,
			const Vector3& lightDirection = Vector3(1.0f, 2.0f, 4.0f));
        virtual ~GlTexDiffusePipeline();

        std::shared_ptr<Texture> getTexture() const override;

		void bind() override;
        void setAttributes() override;
    };
}
