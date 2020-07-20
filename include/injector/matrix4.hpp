#pragma once
#include <injector/defines.hpp>

namespace INJECTOR_NAMESPACE
{
	struct Matrix4
	{
		float m00, m01, m02, m03;
		float m10, m11, m12, m13;
		float m20, m21, m22, m23;
		float m30, m31, m32, m33;

		Matrix4();
		Matrix4(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23, 
			float m30, float m31, float m32, float m33);

		Matrix4 getDot(const Matrix4& other) const noexcept;
		Matrix4 getTransposed() const noexcept;
		float getDeterminant() const noexcept;
		Matrix4 getInversed() const noexcept;

		static const Matrix4 zero;
		static const Matrix4 minusOne;
		static const Matrix4 one;
		static const Matrix4 identity;
	};
}
