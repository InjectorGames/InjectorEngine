#pragma once
#include <injector/graphics/gl_pipeline.hpp>
#include <injector/graphics/color_pipeline.hpp>

namespace INJECTOR_NAMESPACE
{
	class GlColorPipeline : public GlPipeline, public ColorPipeline
	{
	protected:
		GLint mvpLocation;
		GLint colorLocation;

		Matrix4 mvp;
		Vector4 color;
	public:
		static const std::vector<GlVertexAttribute> colorAttributes;

		GlColorPipeline(bool gles,
			const Matrix4& mvp = Matrix4::identity,
			const Vector4& color = Vector4::one);
		virtual ~GlColorPipeline();

		const Matrix4& getMVP() const override;
		void setMVP(const Matrix4& mvp) override;

		const Vector4& getColor() const override;
		void setColor(const Vector4& color) override;

		void bind() override;
	};
}
