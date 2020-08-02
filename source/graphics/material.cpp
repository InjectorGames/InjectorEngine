#include <injector/graphics/material.hpp>

namespace INJECTOR_NAMESPACE
{
	Material::~Material()
	{}

	void Material::use()
	{}
	void Material::unuse()
	{}

	void Material::setModelMatrix(const Matrix4& matrix)
	{}
	void Material::setViewMatrix(const Matrix4& matrix)
	{}
	void Material::setProjMatrix(const Matrix4& matrix)
	{}
	void Material::setViewProjMatrix(const Matrix4& matrix)
	{}
	void Material::setMvpMatrix(const Matrix4& matrix)
	{}
}
