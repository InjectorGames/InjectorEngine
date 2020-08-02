#pragma once
#include <injector/graphics/gl_material.hpp>

namespace INJECTOR_NAMESPACE
{
	class GlColorMaterial : public GlMaterial
	{
	protected:
		int32_t mvpMatrixLocation;
		int32_t colorLocation;
	public:
		static const Vector4 defaultColor;

		GlColorMaterial(const GlShader& vertex, const GlShader& fragment,
			const Vector4& color = defaultColor);
		virtual ~GlColorMaterial();

		void use() override;

		void setMvpMatrix(const Matrix4& matrix) override;
		void setColor(const Vector4& color) noexcept;
	};
}
