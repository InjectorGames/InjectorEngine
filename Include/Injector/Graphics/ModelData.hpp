#pragma once
#include "Injector/Mathematics/Vector4.hpp"

#include <string>
#include <vector>
#include <cstdint>

namespace Injector
{
	struct ModelData
	{
		std::vector<uint16_t> indices16;
		std::vector<uint32_t> indices32;
		std::vector<Vector3> vertices;
		std::vector<Vector4> colors;
		std::vector<Vector2> texCoords;
		std::vector<Vector3> normals;

		ModelData();
		ModelData(
			const std::vector<uint16_t>& indices16,
			const std::vector<uint32_t>& indices32,
			const std::vector<Vector3>& vertices,
			const std::vector<Vector4>& colors,
			const std::vector<Vector2>& texCoords,
			const std::vector<Vector3>& normals);
		virtual ~ModelData();

		std::vector<float> getV() const;
		std::vector<float> getVC() const;
		std::vector<float> getVT() const;
		std::vector<float> getVN() const;
		std::vector<float> getVNT() const;

		static ModelData readFromFile(const std::string& filePath);

		static const std::vector<uint16_t> squareIndices16;
		static const std::vector<uint32_t> squareIndices32;
		static const std::vector<Vector3> squareVertices;
		static const std::vector<Vector4> squareColors;
		static const std::vector<Vector2> squareTexCoords;
		static const std::vector<Vector3> squareNormals;

		static const std::vector<uint16_t> cubeIndices16;
		static const std::vector<uint32_t> cubeIndices32;
		static const std::vector<Vector3> cubeVertices;
		static const std::vector<Vector4> cubeColors;
		static const std::vector<Vector2> cubeTexCoords;
		static const std::vector<Vector3> cubeNormals;

		static const std::vector<uint16_t> frameIndices16;
		static const std::vector<uint32_t> frameIndices32;
		static const std::vector<Vector3> frameVertices;
		static const std::vector<Vector4> frameColors;
		static const std::vector<Vector2> frameTexCoords;
		static const std::vector<Vector3> frameNormals;

		static const std::vector<uint16_t> axisIndices16;
		static const std::vector<uint32_t> axisIndices32;
		static const std::vector<Vector3> axisVertices;
		static const std::vector<Vector4> axisColors;

		static const ModelData square;
		static const ModelData cube;
		static const ModelData frame;
		static const ModelData axis;
	};
}
