#pragma once
#include <injector/graphics/gl_pipeline.hpp>
#include <injector/graphics/diffuse_pipeline.hpp>

namespace injector::graphics
{
    class GlDiffusePipeline : public GlPipeline, public DiffusePipeline
    {
    protected:
        GLint mvpLocation;
        GLint normalLocation;
		GLint objectColorLocation;
        GLint ambientColorLocation;
        GLint lightColorLocation;
        GLint lightDirectionLocation;

        Vector4 objectColor;
        Vector4 ambientColor;
        Vector4 lightColor;
        Vector3 lightDirection;
    public:
        static const std::vector<GlVertexAttribute> vertexAttributes;

        GlDiffusePipeline(
            bool gles,
            const Vector4& objectColor = Vector4::one,
			const Vector4& ambientColor = Vector4::one / 2,
			const Vector4& lightColor = Vector4::one,
			const Vector3& lightDirection = Vector3(1.0f, 2.0f, 4.0f));
        virtual ~GlDiffusePipeline();

        const Vector4& getObjectColor() const override;
		void setObjectColor(const Vector4& objectColor) override;

		const Vector4& getAmbientColor() const override;
		void setAmbientColor(const Vector4& ambientColor) override;

		const Vector4& getLightColor() const override;
		void setLightColor(const Vector4& lightColor) override;

		const Vector3& getLightDirection() const override;
		void setLightDirection(const Vector3& lightDirection) override;

		void flush() override;
		void bind() override;

		void setUniforms(
			const Matrix4& model,
			const Matrix4& view,
			const Matrix4& proj,
			const Matrix4& viewProj,
			const Matrix4& mvp) override;
    };
}
