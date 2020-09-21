#include "Injector/Graphics/ModelData.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	ModelData::ModelData() :
		indices16(),
		indices32(),
		vertices(),
		colors(),
		texCoords(),
		normals()
	{
	}
	ModelData::ModelData(
		const std::vector<uint16_t>& _indices16,
		const std::vector<uint32_t>& _indices32,
		const std::vector<Vector3>& _vertices,
		const std::vector<Vector4>& _colors,
		const std::vector<Vector2>& _texCoords,
		const std::vector<Vector3>& _normals) :
		indices16(_indices16),
		indices32(_indices32),
		vertices(_vertices),
		colors(_colors),
		texCoords(_texCoords),
		normals(_normals)
	{
	}
	ModelData::~ModelData()
	{
	}

	std::vector<float> ModelData::getV() const
	{
		auto vertexData = std::vector<float>(
			vertices.size() * 3);

		memcpy(
			vertexData.data(),
			vertices.data(),
			vertices.size() * sizeof(Vector3));

		return vertexData;
	}
	std::vector<float> ModelData::getVC() const
	{
		if (vertices.size() != colors.size())
		{
			throw Exception(
				"ModelData",
				"getVC",
				"Different array sizes");
		}

		auto vertexData = std::vector<float>(
			vertices.size() * 7);

		for (size_t i = 0, j = 0; i < vertices.size(); i++, j += 7)
		{
			memcpy(
				&vertexData[j],
				&vertices[i],
				sizeof(Vector3));
			memcpy(
				&vertexData[j + 3],
				&colors[i],
				sizeof(Vector4));
		}

		return vertexData;
	}
	std::vector<float> ModelData::getVT() const
	{
		if (vertices.size() != texCoords.size())
		{
			throw Exception(
				"ModelData",
				"getVT",
				"Different array sizes");
		}

		auto vertexData = std::vector<float>(
			vertices.size() * 5);

		for (size_t i = 0, j = 0; i < vertices.size(); i++, j += 5)
		{
			memcpy(
				&vertexData[j],
				&vertices[i],
				sizeof(Vector3));
			memcpy(
				&vertexData[j + 3],
				&texCoords[i],
				sizeof(Vector2));
		}

		return vertexData;
	}
	std::vector<float> ModelData::getVN() const
	{
		if (vertices.size() != normals.size())
		{
			throw Exception(
				"ModelData",
				"getVN",
				"Different array sizes");
		}

		auto vertexData = std::vector<float>(
			vertices.size() * 6);

		for (size_t i = 0, j = 0; i < vertices.size(); i++, j += 6)
		{
			memcpy(
				&vertexData[j],
				&vertices[i],
				sizeof(Vector3));
			memcpy(
				&vertexData[j + 3],
				&normals[i],
				sizeof(Vector3));
		}

		return vertexData;
	}
	std::vector<float> ModelData::getVNT() const
	{
		if (vertices.size() != normals.size() ||
			vertices.size() != texCoords.size())
		{
			throw Exception(
				"ModelData",
				"getVNT",
				"Different array sizes");
		}

		auto vertexData = std::vector<float>(
			vertices.size() * 8);

		for (size_t i = 0, j = 0; i < vertices.size(); i++, j += 8)
		{
			memcpy(
				&vertexData[j],
				&vertices[i],
				sizeof(Vector3));
			memcpy(
				&vertexData[j + 3],
				&normals[i],
				sizeof(Vector3));
			memcpy(
				&vertexData[j + 6],
				&texCoords[i],
				sizeof(Vector2));
		}

		return vertexData;
	}

	const std::vector<uint16_t> ModelData::squareIndices16 = {
		0, 1, 2, 0, 2, 3,
	};
	const std::vector<uint32_t> ModelData::squareIndices32 = {
		0, 1, 2, 0, 2, 3,
	};
	const std::vector<Vector3> ModelData::squareVertices = {
		Vector3(-0.5f, -0.5f, 0.0f),
		Vector3(-0.5f, 0.5f, 0.0f),
		Vector3(0.5f, 0.5f, 0.0f),
		Vector3(0.5f, -0.5f, 0.0f),
	};
	const std::vector<Vector4> ModelData::squareColors = {
		Vector4(1.0f, 0.0f, 0.0f, 1.0f),
		Vector4(0.0f, 1.0f, 0.0f, 1.0f),
		Vector4(0.0f, 0.0f, 1.0f, 1.0f),
		Vector4(1.0f, 0.0f, 1.0f, 1.0f),
	};
	const std::vector<Vector2> ModelData::squareTexCoords = {
		Vector2(0.0f, 0.0f),
		Vector2(0.0f, 1.0f),
		Vector2(1.0f, 1.0f),
		Vector2(1.0f, 0.0f),
	};
	const std::vector<Vector3> ModelData::squareNormals = {
		Vector3(0.0f, 0.0f, -1.0f),
		Vector3(0.0f, 0.0f, -1.0f),
		Vector3(0.0f, 0.0f, -1.0f),
		Vector3(0.0f, 0.0f, -1.0f),
	};

	const std::vector<uint16_t> ModelData::cubeIndices16 = {
		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23,
	};
	const std::vector<uint32_t> ModelData::cubeIndices32 = {
		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23,
	};
	const std::vector<Vector3> ModelData::cubeVertices = {
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
	const std::vector<Vector4> ModelData::cubeColors = {
		Vector4(1.0f, 0.0f, 0.0f, 1.0f),
		Vector4(0.0f, 1.0f, 0.0f, 1.0f),
		Vector4(0.0f, 0.0f, 1.0f, 1.0f),
		Vector4(1.0f, 0.0f, 1.0f, 1.0f),

		Vector4(1.0f, 0.0f, 0.0f, 1.0f),
		Vector4(0.0f, 1.0f, 0.0f, 1.0f),
		Vector4(0.0f, 0.0f, 1.0f, 1.0f),
		Vector4(1.0f, 0.0f, 1.0f, 1.0f),

		Vector4(1.0f, 0.0f, 0.0f, 1.0f),
		Vector4(0.0f, 1.0f, 0.0f, 1.0f),
		Vector4(0.0f, 0.0f, 1.0f, 1.0f),
		Vector4(1.0f, 0.0f, 1.0f, 1.0f),

		Vector4(1.0f, 0.0f, 0.0f, 1.0f),
		Vector4(0.0f, 1.0f, 0.0f, 1.0f),
		Vector4(0.0f, 0.0f, 1.0f, 1.0f),
		Vector4(1.0f, 0.0f, 1.0f, 1.0f),

		Vector4(1.0f, 0.0f, 0.0f, 1.0f),
		Vector4(0.0f, 1.0f, 0.0f, 1.0f),
		Vector4(0.0f, 0.0f, 1.0f, 1.0f),
		Vector4(1.0f, 0.0f, 1.0f, 1.0f),

		Vector4(1.0f, 0.0f, 0.0f, 1.0f),
		Vector4(0.0f, 1.0f, 0.0f, 1.0f),
		Vector4(0.0f, 0.0f, 1.0f, 1.0f),
		Vector4(1.0f, 0.0f, 1.0f, 1.0f),
	};
	const std::vector<Vector2> ModelData::cubeTexCoords = {
		Vector2(0.0f, 0.0f),
		Vector2(0.0f, 1.0f),
		Vector2(1.0f, 1.0f),
		Vector2(1.0f, 0.0f),

		Vector2(0.0f, 0.0f),
		Vector2(0.0f, 1.0f),
		Vector2(1.0f, 1.0f),
		Vector2(1.0f, 0.0f),

		Vector2(0.0f, 0.0f),
		Vector2(0.0f, 1.0f),
		Vector2(1.0f, 1.0f),
		Vector2(1.0f, 0.0f),

		Vector2(0.0f, 0.0f),
		Vector2(0.0f, 1.0f),
		Vector2(1.0f, 1.0f),
		Vector2(1.0f, 0.0f),

		Vector2(0.0f, 0.0f),
		Vector2(0.0f, 1.0f),
		Vector2(1.0f, 1.0f),
		Vector2(1.0f, 0.0f),

		Vector2(0.0f, 0.0f),
		Vector2(0.0f, 1.0f),
		Vector2(1.0f, 1.0f),
		Vector2(1.0f, 0.0f),
	};
	const std::vector<Vector3> ModelData::cubeNormals = {
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

	const std::vector<uint16_t> ModelData::frameIndices16 = {
		0, 1, 2, 0, 2, 3,
	};
	const std::vector<uint32_t> ModelData::frameIndices32 = {
		0, 1, 2, 0, 2, 3,
	};
	const std::vector<Vector3> ModelData::frameVertices = {
		Vector3(-1.0f, -1.0f, 0.0f),
		Vector3(-1.0f, 1.0f, 0.0f),
		Vector3(1.0f, 1.0f, 0.0f),
		Vector3(1.0f, -1.0f, 0.0f),
	};
	const std::vector<Vector4> ModelData::frameColors = {
		Vector4(1.0f, 0.0f, 0.0f, 1.0f),
		Vector4(0.0f, 1.0f, 0.0f, 1.0f),
		Vector4(0.0f, 0.0f, 1.0f, 1.0f),
		Vector4(1.0f, 0.0f, 1.0f, 1.0f),
	};
	const std::vector<Vector2> ModelData::frameTexCoords = {
		Vector2(0.0f, 0.0f),
		Vector2(0.0f, 1.0f),
		Vector2(1.0f, 1.0f),
		Vector2(1.0f, 0.0f),
	};
	const std::vector<Vector3> ModelData::frameNormals = {
		Vector3(0.0f, 0.0f, -1.0f),
		Vector3(0.0f, 0.0f, -1.0f),
		Vector3(0.0f, 0.0f, -1.0f),
		Vector3(0.0f, 0.0f, -1.0f),
	};

	const std::vector<uint16_t> ModelData::axisIndices16 = {
		0, 1, 2, 3, 4, 5,
	};
	const std::vector<uint32_t> ModelData::axisIndices32 = {
		0, 1, 2, 3, 4, 5,
	};
	const std::vector<Vector3> ModelData::axisVertices = {
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 0.0f, 0.0f),
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(0.0f, 1.0f, 0.0f),
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(0.0f, 0.0f, 1.0f),
	};
	const std::vector<Vector4> ModelData::axisColors = {
		Vector4(1.0f, 0.0f, 0.0f, 1.0f),
		Vector4(1.0f, 0.0f, 0.0f, 1.0f),
		Vector4(0.0f, 1.0f, 0.0f, 1.0f),
		Vector4(0.0f, 1.0f, 0.0f, 1.0f),
		Vector4(0.0f, 0.0f, 1.0f, 1.0f),
		Vector4(0.0f, 0.0f, 1.0f, 1.0f),
	};

	const ModelData ModelData::square = ModelData(
		squareIndices16,
		squareIndices32,
		squareVertices,
		squareColors,
		squareTexCoords,
		squareNormals);
	const ModelData ModelData::cube = ModelData(
		cubeIndices16,
		cubeIndices32,
		cubeVertices,
		cubeColors,
		cubeTexCoords,
		cubeNormals);
	const ModelData ModelData::frame = ModelData(
		frameIndices16,
		frameIndices32,
		frameVertices,
		frameColors,
		frameTexCoords,
		frameNormals);
	const ModelData ModelData::axis = ModelData(
		axisIndices16,
		axisIndices32,
		axisVertices,
		axisColors,
		{},
		{});
}
