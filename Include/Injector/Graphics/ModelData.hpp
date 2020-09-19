#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace Injector
{
	class ModelData
	{
	 public:
		ModelData();
		virtual ~ModelData();

		static std::shared_ptr<ModelData> readFromFile(
			const std::string& filePath);

		static const ModelData square;
	};
}