#pragma once
#include "Injector/Graphics/GlPipeline.hpp"
#include "Injector/Graphics/DiffusePipeline.hpp"
#include "Injector/Graphics/GlBuffer.hpp"

namespace Injector
{
    class GlDiffusePipeline : public GlPipeline, public DiffusePipeline
    {
    public:
        struct UniformBufferObject
		{
			Vector4 objectColor;
			Vector4 ambientColor;
			Vector4 lightColor;
			alignas(16) Vector3 lightDirection;

			UniformBufferObject(
				const Vector4& _objectColor,
				const Vector4& _ambientColor,
				const Vector4& _lightColor,
				const Vector3& _lightDirection) :
				objectColor(_objectColor),
				ambientColor(_ambientColor),
				lightColor(_lightColor),
				lightDirection(_lightDirection)
			{}
		};
    protected:
        GLint mvpLocation;
        GLint normalLocation;
        std::shared_ptr<GlBuffer> uniformBuffer;
        UniformBufferObject ubo;
    public:
        GlDiffusePipeline(bool gles,
            const Vector4& objectColor = Vector4::one,
			const Vector4& ambientColor = Vector4::one / 2,
			const Vector4& lightColor = Vector4::one,
			const Vector3& lightDirection = Vector3(1.0f, 2.0f, 3.0f));
        virtual ~GlDiffusePipeline();

        const Vector4& getObjectColor() const override;
		void setObjectColor(const Vector4& objectColor) override;

		const Vector4& getAmbientColor() const override;
		void setAmbientColor(const Vector4& ambientColor) override;

		const Vector4& getLightColor() const override;
		void setLightColor(const Vector4& lightColor) override;

		const Vector3& getLightDirection() const override;
		void setLightDirection(const Vector3& lightDirection) override;

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
