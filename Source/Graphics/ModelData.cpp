#include "Injector/Graphics/ModelData.hpp"
#include "Injector/Exception/Exception.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace Injector
{
	ModelData::ModelData()
	{
	}
	ModelData::~ModelData()
	{
	}

	std::shared_ptr<ModelData> ModelData::readFromFile(
		const std::string& filePath)
	{
		auto importer = Assimp::Importer();
		auto scene = importer.ReadFile(filePath, {});

		if (!scene)
			throw Exception("ModelData", "readFromFile", "Failed to read file");
	}
}