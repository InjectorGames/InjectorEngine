#include "Injector/Graphics/ModelData.hpp"
#include "Injector/Exception/Exception.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Injector
{
	ModelData::ModelData() :
		indices(),
		vertices(),
		colors(),
		texCoords(),
		normals(),
		tangents(),
		bitangents()
	{
	}
	ModelData::ModelData(
		const std::vector<uint32_t>& _indices,
		const std::vector<Vector3>& _vertices,
		const std::vector<Vector4>& _colors,
		const std::vector<Vector2>& _texCoords,
		const std::vector<Vector3>& _normals,
		const std::vector<Vector3>& _tangents,
		const std::vector<Vector3>& _bitangents) :
		indices(_indices),
		vertices(_vertices),
		colors(_colors),
		texCoords(_texCoords),
		normals(_normals),
		tangents(_tangents),
		bitangents(_bitangents)
	{
	}

	std::vector<float> ModelData::getVertex() const
	{
		auto vertexData = std::vector<float>(
			vertices.size() * 3);

		memcpy(
			vertexData.data(),
			vertices.data(),
			vertices.size() * sizeof(Vector3));

		return std::move(vertexData);
	}
	std::vector<float> ModelData::getVertexColor() const
	{
		if (vertices.size() != colors.size())
		{
			throw Exception(
				THIS_FUNCTION_NAME,
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

		return std::move(vertexData);
	}
	std::vector<float> ModelData::getVertexTexCoord() const
	{
		if (vertices.size() != texCoords.size())
		{
			throw Exception(
				THIS_FUNCTION_NAME,
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

		return std::move(vertexData);
	}
	std::vector<float> ModelData::getVertexNormal() const
	{
		if (vertices.size() != normals.size())
		{
			throw Exception(
				THIS_FUNCTION_NAME,
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

		return std::move(vertexData);
	}
	std::vector<float> ModelData::getVertexNormalTexCoord() const
	{
		if (vertices.size() != normals.size() ||
			vertices.size() != texCoords.size())
		{
			throw Exception(
				THIS_FUNCTION_NAME,
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

		return std::move(vertexData);
	}

	std::shared_ptr<ModelData> ModelData::readFromFile(
		const std::string& filePath)
	{
		auto importer = Assimp::Importer();

		auto scene = importer.ReadFile(filePath,
			aiProcessPreset_TargetRealtime_Fast |
			aiProcess_MakeLeftHanded |
			aiProcess_FlipWindingOrder);

		if (!scene)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to load scene");
		}
		if (!scene->HasMeshes())
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Scene has no meshes");
		}
		if (scene->mNumMeshes > 1)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Scene has more than one mesh");
		}

		auto modelData = std::make_shared<ModelData>();
		auto mesh = scene->mMeshes[0];

		auto vertexCount = mesh->mNumVertices;
		modelData->vertices.resize(vertexCount);

		memcpy(
			modelData->vertices.data(),
			mesh->mVertices,
			vertexCount * sizeof(Vector3));

		if (mesh->HasFaces())
		{
			auto& indices = modelData->indices;

			for (uint32_t i = 0; i < mesh->mNumFaces; i++)
			{
				auto face = mesh->mFaces[i];

				for (uint32_t j = 0; j < face.mNumIndices; j++)
					indices.push_back(face.mIndices[j]);
			}
		}

		if(mesh->HasVertexColors(0))
		{
			modelData->colors.resize(vertexCount);

			memcpy(
				modelData->colors.data(),
				mesh->mColors[0],
				vertexCount * sizeof(Vector4));
		}

		if (mesh->HasTextureCoords(0))
		{
			auto& texCoords = modelData->texCoords;
			auto textureCoords = mesh->mTextureCoords[0];
			texCoords.resize(vertexCount);

			for (uint32_t i = 0; i < vertexCount; i++)
			{
				memcpy(
					&texCoords[i],
					&textureCoords[i],
					sizeof(Vector2));
			}
		}

		if (mesh->HasNormals())
		{
			modelData->normals.resize(vertexCount);

			memcpy(
				modelData->normals.data(),
				mesh->mNormals,
				vertexCount * sizeof(Vector3));
		}

		if(mesh->HasTangentsAndBitangents())
		{
			modelData->tangents.resize(vertexCount);
			modelData->bitangents.resize(vertexCount);

			memcpy(
				modelData->tangents.data(),
				mesh->mTangents,
				vertexCount * sizeof(Vector3));
			memcpy(
				modelData->bitangents.data(),
				mesh->mBitangents,
				vertexCount * sizeof(Vector3));
		}

		return modelData;
	}

	const std::vector<uint32_t> ModelData::squareIndices = {
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

	const std::vector<uint32_t> ModelData::cubeIndices = {
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

	const std::vector<uint32_t> ModelData::frameIndices = {
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

	const std::vector<uint32_t> ModelData::axisIndices = {
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

	// TODO: Compute tangents and bitangets

	const ModelData ModelData::square = ModelData(
		squareIndices,
		squareVertices,
		squareColors,
		squareTexCoords,
		squareNormals,
		{},
		{});
	const ModelData ModelData::cube = ModelData(
		cubeIndices,
		cubeVertices,
		cubeColors,
		cubeTexCoords,
		cubeNormals,
		{},
		{});
	const ModelData ModelData::frame = ModelData(
		frameIndices,
		frameVertices,
		frameColors,
		frameTexCoords,
		frameNormals,
		{},
		{});
	const ModelData ModelData::axis = ModelData(
		axisIndices,
		axisVertices,
		axisColors,
		{},
		{},
		{},
		{});
}
