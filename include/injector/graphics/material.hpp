#pragma once
#include <injector/graphics/shader.hpp>
#include <injector/mathematics/matrix4.hpp>

namespace INJECTOR_NAMESPACE
{
	class Material
	{
	public:
		virtual ~Material();

		virtual void use();
		virtual void unuse();

		virtual void setModelMatrix(const Matrix4& matrix);
		virtual void setViewMatrix(const Matrix4& matrix);
		virtual void setProjMatrix(const Matrix4& matrix);
		virtual void setViewProjMatrix(const Matrix4& matrix);
		virtual void setMvpMatrix(const Matrix4& matrix);
	};

	using MaterialHandle = std::shared_ptr<Material>;
}