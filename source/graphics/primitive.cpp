#include <injector/graphics/primitive.hpp>

namespace INJECTOR_NAMESPACE
{
	const std::vector<Vector3> Primitive::squareVertices =
	{
		Vector3(-0.5f, -0.5f, 0.0f),
		Vector3(-0.5f, 0.5f, 0.0f), 
		Vector3(0.5f, 0.5f, 0.0f),
		Vector3(0.5f, -0.5f, 0.0f),
	};
	const std::vector<Vector3> Primitive::squareNormals =
	{
		Vector3(0.0f, 0.0f, -1.0f),
		Vector3(0.0f, 0.0f, -1.0f),
		Vector3(0.0f, 0.0f, -1.0f),
		Vector3(0.0f, 0.0f, -1.0f),
	};
	const std::vector<uint16_t> Primitive::squareIndices =
	{
		0, 1, 2, 0, 2, 3,
	};

	const std::vector<Vector3> Primitive::cubeVertices =
	{
		Vector3(-0.5f, -0.5f, 0.5f),
		Vector3(-0.5f, 0.5f, 0.5f),
		Vector3(-0.5f, 0.5f, -0.5f),
		Vector3(-0.5f, -0.5f, -0.5f),

		Vector3(0.5f, -0.5f, -0.5f),
		Vector3(0.5f, 0.5f, -0.5f),
		Vector3(0.5f, 0.5f, 0.5f),
		Vector3(0.5f, -0.5f, 0.5f),

		Vector3(-0.5f, -0.5f, 0.5f),
		Vector3(-0.5f, -0.5f, -0.5f),
		Vector3(0.5f, -0.5f, -0.5f),
		Vector3(0.5f, -0.5f, 0.5f),

		Vector3(-0.5f, 0.5f, -0.5f),
		Vector3(-0.5f, 0.5f, 0.5f),
		Vector3(0.5f, 0.5f, 0.5f),
		Vector3(0.5f, 0.5f, -0.5f),

		Vector3(-0.5f, -0.5f, -0.5f),
		Vector3(-0.5f, 0.5f, -0.5f),
		Vector3(0.5f, 0.5f, -0.5f),
		Vector3(0.5f, -0.5f, -0.5f),

		Vector3(0.5f, -0.5f, 0.5f),
		Vector3(0.5f, 0.5f, 0.5f),
		Vector3(-0.5f, 0.5f, 0.5f),
		Vector3(-0.5f, -0.5f, 0.5f),
	};
	const std::vector<Vector3> Primitive::cubeNormals =
	{
		Vector3(-1.0f, 0.0f, 0.0f), 
		Vector3(-1.0f, 0.0f, 0.0f), 
		Vector3(-1.0f, 0.0f, 0.0f),
		Vector3(-1.0f, 0.0f, 0.0f),

		Vector3(1.0f, 0.0f, 0.0f), 
		Vector3(1.0f, 0.0f, 0.0f),
		Vector3(1.0f, 0.0f, 0.0f), 
		Vector3(1.0f, 0.0f, 0.0f),

		Vector3(0.0f, -1.0f, 0.0f),
		Vector3(0.0f, -1.0f, 0.0f),
		Vector3(0.0f, -1.0f, 0.0f), 
		Vector3(0.0f, -1.0f, 0.0f),

		Vector3(0.0f, 1.0f, 0.0f), 
		Vector3(0.0f, 1.0f, 0.0f), 
		Vector3(0.0f, 1.0f, 0.0f), 
		Vector3(0.0f, 1.0f, 0.0f),

		Vector3(0.0f, 0.0f, -1.0f),
		Vector3(0.0f, 0.0f, -1.0f),
		Vector3(0.0f, 0.0f, -1.0f),
		Vector3(0.0f, 0.0f, -1.0f),

		Vector3(0.0f, 0.0f, 1.0f),
		Vector3(0.0f, 0.0f, 1.0f), 
		Vector3(0.0f, 0.0f, 1.0f), 
		Vector3(0.0f, 0.0f, 1.0f),
	};
	const std::vector<uint16_t> Primitive::cubeIndices =
	{
		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23,
	};

	const std::vector<Vector3> Primitive::axisVertices =
	{
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 0.0f, 0.0f),
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(0.0f, 1.0f, 0.0f),
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(0.0f, 0.0f, 1.0f),
	};
	const std::vector<Vector3> Primitive::axisColors =
	{
		Vector3(1.0f, 0.0f, 0.0f), 
		Vector3(1.0f, 0.0f, 0.0f),
		Vector3(0.0f, 1.0f, 0.0f),
		Vector3(0.0f, 1.0f, 0.0f),
		Vector3(0.0f, 0.0f, 1.0f),
		Vector3(0.0f, 0.0f, 1.0f),
	};
	const std::vector<uint16_t> Primitive::axisIndices =
	{
		0, 1, 2, 3, 4, 5,
	};
}
