#pragma once
#include <injector/defines.hpp>

namespace INJECTOR_NAMESPACE
{
	struct Matrix2
	{
		float m00, m01;
		float m10, m11;

		Matrix2();
		Matrix2(
			float m00, float m01,
			float m10, float m11);

		Matrix2 getDot(const Matrix2& other) const noexcept;
		Matrix2 getTransposed() const noexcept;
		float getDeterminant() const noexcept;
		Matrix2 getInversed() const noexcept;

		static const Matrix2 zero;
		static const Matrix2 minusOne;
		static const Matrix2 one;
		static const Matrix2 identity;
	};
}
