#pragma once
#include <injector/mathematics/vector3.hpp>

#include <vector>
#include <cstdint>

namespace injector::graphics
{
	class Primitive
	{
	public:
		static const std::vector<Vector3> squareVertices;
		static const std::vector<Vector3> squareNormals;
		static const std::vector<uint16_t> squareIndices;

		static const std::vector<Vector3> cubeVertices;
		static const std::vector<Vector3> cubeNormals;
		static const std::vector<uint16_t> cubeIndices;

		static const std::vector<Vector3> axisVertices;
		static const std::vector<Vector3> axisColors;
		static const std::vector<uint16_t> axisIndices;

		// TODO: replace with sphere skybox
		/*static const std::vector<float> gradientSkyVertices;
		static const std::vector<uint16_t> gradientSkyIndices;*/
	};
}
