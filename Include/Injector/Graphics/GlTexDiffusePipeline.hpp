#pragma once
#include "Injector/Graphics/GlDiffusePipeline.hpp"
#include "Injector/Graphics/TexDiffusePipeline.hpp"
#include "Injector/Graphics/GlTexture.hpp"

namespace Injector
{
    class GlTexDiffusePipeline : public GlPipeline, public TexDiffusePipeline
    {
    public:
        struct UniformBufferObject
		{
			Vector4 objectColor;
			Vector4 ambientColor;
			Vector4 lightColor;
			Vector3 lightDirection;
            float aligment;
            Vector2 textureScale;
            Vector2 textureOffset;

			UniformBufferObject(
				const Vector4& _objectColor,
				const Vector4& _ambientColor,
				const Vector4& _lightColor,
				const Vector3& _lightDirection,
                const Vector2& _textureScale,
                const Vector2& _textureOffset) :
				objectColor(_objectColor),
				ambientColor(_ambientColor),
				lightColor(_lightColor),
				lightDirection(_lightDirection),
                aligment(0.0f),
                textureScale(_textureScale),
                textureOffset(_textureOffset)
			{}
		};
    protected:
        GLint mvpLocation;
        GLint normalLocation;
        GLint textureLocation;
        std::shared_ptr<GlBuffer> uniformBuffer;
        std::shared_ptr<GlTexture> texture;
        UniformBufferObject ubo;
    public:
        GlTexDiffusePipeline(bool gles,
            const std::shared_ptr<GlTexture>& texture,
            const Vector4& objectColor = Vector4::one,
			const Vector4& ambientColor = Vector4::one / 2,
			const Vector4& lightColor = Vector4::one,
			const Vector3& lightDirection = Vector3(1.0f, 2.0f, 3.0f),
            const Vector2& textureScale = Vector2::one,
            const Vector2& textureOffset = Vector2::zero);
        virtual ~GlTexDiffusePipeline();

        std::shared_ptr<Texture> getTexture() const override;

        const Vector4& getObjectColor() const override;
		void setObjectColor(const Vector4& objectColor) override;

		const Vector4& getAmbientColor() const override;
		void setAmbientColor(const Vector4& ambientColor) override;

		const Vector4& getLightColor() const override;
		void setLightColor(const Vector4& lightColor) override;

		const Vector3& getLightDirection() const override;
		void setLightDirection(const Vector3& lightDirection) override;

        const Vector2& getTextureScale() const override;
		void setTextureScale(const Vector2& textureScale) override;

        const Vector2& getTextureOffset() const override;
		void setTextureOffset(const Vector2& textureOffset) override;

		void bind() override;
        void flush() override;
        void setAttributes() override;

		void setUniforms(
			const Matrix4& model,
			const Matrix4& view,
			const Matrix4& proj,
			const Matrix4& viewProj,
			const Matrix4& mvp) override;
    };
}
