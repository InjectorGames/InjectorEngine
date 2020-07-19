#pragma once
#include <injector/defines.hpp>

namespace INJECTOR_NAMESPACE
{
	struct Matrix4
	{
		float v00, v01, v02, v03;
		float v10, v11, v12, v13;
		float v20, v21, v22, v23;
		float v30, v31, v32, v33;

		Matrix4(
			float v00 = 0.0f, float v01 = 0.0f, float v02 = 0.0f, float v03 = 0.0f,
			float v10 = 0.0f, float v11 = 0.0f, float v12 = 0.0f, float v13 = 0.0f,
			float v20 = 0.0f, float v21 = 0.0f, float v22 = 0.0f, float v23 = 0.0f, 
			float v30 = 0.0f, float v31 = 0.0f, float v32 = 0.0f, float v33 = 0.0f);

		Matrix4 getDot(const Matrix4& other) const noexcept;

		static const Matrix4 zero;
		static const Matrix4 minusOne;
		static const Matrix4 one;
		static const Matrix4 identity;
	};
}
