//#include <injector/graphics/gl_color_material.hpp>

namespace INJECTOR_NAMESPACE
{
	/*const Vector4 GlColorMaterial::defaultColor = Vector4::one;

	GlColorMaterial::GlColorMaterial(
		const GlShader& vertex,
		const GlShader& fragment,
		const Vector4& color) :
		GlMaterial(vertex, fragment)
	{
		mvpMatrixLocation = getUniformLocation("u_MvpMatrix");
		colorLocation = getUniformLocation("u_Color");

		use();
		setColor(color);
		unuse();
	}
	GlColorMaterial::~GlColorMaterial()
	{}

	void GlColorMaterial::use()
	{
		enableDepthTest();
		disableBlend();
		GlMaterial::use();
	}

	void GlColorMaterial::setMvpMatrix(const Matrix4& matrix)
	{
		setUniform(mvpMatrixLocation, matrix);
	}
	void GlColorMaterial::setColor(const Vector4& color) noexcept
	{
		setUniform(colorLocation, color);
	}*/
}
