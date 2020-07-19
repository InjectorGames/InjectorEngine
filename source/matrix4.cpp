#include <injector/matrix4.hpp>

namespace INJECTOR_NAMESPACE
{
	Matrix4::Matrix4(
		float _v00, float _v01, float _v02, float _v03,
		float _v10, float _v11, float _v12, float _v13,
		float _v20, float _v21, float _v22, float _v23,
		float _v30, float _v31, float _v32, float _v33) :
		v00(_v00), v01(_v01), v02(_v02), v03(_v03),
		v10(_v10), v11(_v11), v12(_v12), v13(_v13),
		v20(_v20), v21(_v21), v22(_v22), v23(_v23),
		v30(_v30), v31(_v31), v32(_v32), v33(_v33)
	{}

	Matrix4 Matrix4::getDot(const Matrix4& other) const noexcept
	{
		return Matrix4(
			v00 * other.v00 + v01 * other.v10 + v02 * other.v20 + v03 * other.v30,
			v00 * other.v01 + v01 * other.v11 + v02 * other.v21 + v03 * other.v31,
			v00 * other.v02 + v01 * other.v12 + v02 * other.v22 + v03 * other.v32,
			v00 * other.v03 + v01 * other.v13 + v02 * other.v23 + v03 * other.v33,

			v10 * other.v00 + v11 * other.v10 + v12 * other.v20 + v13 * other.v30,
			v10 * other.v01 + v11 * other.v11 + v12 * other.v21 + v13 * other.v31,
			v10 * other.v02 + v11 * other.v12 + v12 * other.v22 + v13 * other.v32,
			v10 * other.v03 + v11 * other.v13 + v12 * other.v23 + v13 * other.v33,

			v20 * other.v00 + v21 * other.v10 + v22 * other.v20 + v23 * other.v30,
			v20 * other.v01 + v21 * other.v11 + v22 * other.v21 + v23 * other.v31,
			v20 * other.v02 + v21 * other.v12 + v22 * other.v22 + v23 * other.v32,
			v20 * other.v03 + v21 * other.v13 + v22 * other.v23 + v23 * other.v33,

			v30 * other.v00 + v31 * other.v10 + v32 * other.v20 + v33 * other.v30,
			v30 * other.v01 + v31 * other.v11 + v32 * other.v21 + v33 * other.v31,
			v30 * other.v02 + v31 * other.v12 + v32 * other.v22 + v33 * other.v32,
			v30 * other.v03 + v31 * other.v13 + v32 * other.v23 + v33 * other.v33);
	}

	const Matrix4 Matrix4::zero = Matrix4(
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 
		0.0f, 0.0f, 0.0f, 0.0f, 
		0.0f, 0.0f, 0.0f, 0.0f);
	const Matrix4 Matrix4::minusOne = Matrix4(
		-1.0f, -1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f, -1.0f);
	const Matrix4 Matrix4::one = Matrix4(
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f);
	const Matrix4 Matrix4::identity = Matrix4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}
