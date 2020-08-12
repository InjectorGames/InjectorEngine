#pragma once
#include <injector/defines.hpp>

#include <vector>
#include <cstdint>

namespace INJECTOR_NAMESPACE
{
	class Primitive
	{
	public:
		static const std::vector<float> squareVertices;
		static const std::vector<float> squareNormals;
		static const std::vector<uint16_t> squareIndices;

		static const std::vector<float> cubeVertices;
		static const std::vector<float> cubeNormals;
		static const std::vector<uint16_t> cubeIndices;

		static const std::vector<float> axisVertices;
		static const std::vector<float> axisColors;
		static const std::vector<uint16_t> axisIndices;

		// TODO: replace with sphere skybox
		static const std::vector<float> gradientSkyVertices;
		static const std::vector<uint16_t> gradientSkyIndices;
	};
}
