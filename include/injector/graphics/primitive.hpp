#pragma once
#include "Injector/Mathematics/Vector3.hpp"

#include <vector>
#include <cstdint>

namespace Injector::Graphics
{
	using namespace std;
	using namespace Injector::Mathematics;

	class Primitive
	{
	public:
		static const vector<Vector3> squareVertices;
		static const vector<Vector3> squareNormals;
		static const vector<uint16_t> squareIndices;

		static const vector<Vector3> cubeVertices;
		static const vector<Vector3> cubeNormals;
		static const vector<uint16_t> cubeIndices;

		static const vector<Vector3> axisVertices;
		static const vector<Vector3> axisColors;
		static const vector<uint16_t> axisIndices;
	};
}
