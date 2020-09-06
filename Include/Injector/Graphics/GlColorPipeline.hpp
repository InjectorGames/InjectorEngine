#pragma once
#include "Injector/Graphics/GlPipeline.hpp"
#include "Injector/Graphics/ColorPipeline.hpp"

namespace Injector::Graphics
{
	class GlColorPipeline : public GlPipeline, public ColorPipeline
	{
	protected:
		GLint mvpLocation;
		GLint colorLocation;

		Vector4 color;
	public:
		static const vector<GlVertexAttribute> vertexAttributes;

		GlColorPipeline(bool gles,
			const Vector4& color = Vector4::one);
		virtual ~GlColorPipeline();

		const Vector4& getColor() const override;
		void setColor(const Vector4& color) override;

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
