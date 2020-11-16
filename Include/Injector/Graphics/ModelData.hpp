#pragma once
#include "Injector/Mathematics/Vector4.hpp"

#include <string>
#include <vector>
#include <memory>
#include <cstdint>

namespace Injector
{
	struct ModelData
	{
		std::vector<uint32_t> indices;
		std::vector<FloatVector3> vertices;
		std::vector<FloatVector4> colors;
		std::vector<FloatVector2> texCoords;
		std::vector<FloatVector3> normals;
		std::vector<FloatVector3> tangents;
		std::vector<FloatVector3> bitangents;

		ModelData();
		ModelData(
			const std::vector<uint32_t>& indices,
			const std::vector<FloatVector3>& vertices,
			const std::vector<FloatVector4>& colors,
			const std::vector<FloatVector2>& texCoords,
			const std::vector<FloatVector3>& normals,
			const std::vector<FloatVector3>& tangents,
			const std::vector<FloatVector3>& bitangents);
		// TODO: move/copy constructor
		virtual ~ModelData() = default;

		// TODO: add texture loading,
		// add getVertex status method "bool isXXX();"

		std::vector<float> getVertex() const;
		std::vector<float> getVertexColor() const;
		std::vector<float> getVertexTexCoord() const;
		std::vector<float> getVertexNormal() const;
		std::vector<float> getVertexNormalTexCoord() const;

		static std::shared_ptr<ModelData> readFromFile(
			const std::string& filePath);

		static const std::vector<uint32_t> squareIndices;
		static const std::vector<FloatVector3> squareVertices;
		static const std::vector<FloatVector4> squareColors;
		static const std::vector<FloatVector2> squareTexCoords;
		static const std::vector<FloatVector3> squareNormals;

		static const std::vector<uint32_t> cubeIndices;
		static const std::vector<FloatVector3> cubeVertices;
		static const std::vector<FloatVector4> cubeColors;
		static const std::vector<FloatVector2> cubeTexCoords;
		static const std::vector<FloatVector3> cubeNormals;

		static const std::vector<uint32_t> frameIndices;
		static const std::vector<FloatVector3> frameVertices;
		static const std::vector<FloatVector4> frameColors;
		static const std::vector<FloatVector2> frameTexCoords;
		static const std::vector<FloatVector3> frameNormals;

		static const std::vector<uint32_t> axisIndices;
		static const std::vector<FloatVector3> axisVertices;
		static const std::vector<FloatVector4> axisColors;

		static const ModelData square;
		static const ModelData cube;
		static const ModelData frame;
		static const ModelData axis;
	};
}
