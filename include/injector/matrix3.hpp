#pragma once
#include <injector/defines.hpp>

namespace INJECTOR_NAMESPACE
{
	struct Matrix3
	{
		float m00, m01, m02;
		float m10, m11, m12;
		float m20, m21, m22;

		Matrix3();
		Matrix3(
			float m00, float m01, float m02,
			float m10, float m11, float m12,
			float m20, float m21, float m22);

		Matrix3 getDot(const Matrix3& other) const noexcept;
		Matrix3 getTransposed() const noexcept;
		float getDeterminant() const noexcept;
		Matrix3 getInversed() const noexcept;

		static const Matrix3 zero;
		static const Matrix3 minusOne;
		static const Matrix3 one;
		static const Matrix3 identity;
	};
}
