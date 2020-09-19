#pragma once
#include "Injector/Graphics/ModelData.hpp"
#include "Injector/Mathematics/Vector3.hpp"

namespace Injector
{
	class BasicModel
	{
	 public:
		static const std::vector<Vector3> squareVertices;
		static const std::vector<Vector3> squareNormals;
		static const std::vector<Vector2> squareTexCoords;
		static const std::vector<uint16_t> squareIndices;

		static const std::vector<Vector3> cubeVertices;
		static const std::vector<Vector3> cubeNormals;
		static const std::vector<Vector2> cubeTexCoords;
		static const std::vector<uint16_t> cubeIndices;

		static const std::vector<Vector3> frameVertices;
		static const std::vector<Vector3> frameNormals;
		static const std::vector<Vector2> frameTexCoords;
		static const std::vector<Vector3> frameIndices;

		static const std::vector<Vector3> axisVertices;
		static const std::vector<Vector3> axisColors;
		static const std::vector<uint16_t> axisIndices;
	};
}
