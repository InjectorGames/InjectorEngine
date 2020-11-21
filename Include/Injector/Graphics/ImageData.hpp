#pragma once
#include "Injector/Mathematics/Vector3.hpp"

#include <vector>
#include <string>
#include <memory>

namespace Injector
{
	struct ImageData
	{
		SizeVector3 size;
		int componentCount;
		bool component16;
		std::vector<uint8_t> pixels;

		ImageData();
		ImageData(
			const SizeVector3& size,
			int componentCount,
			bool component16,
			const std::vector<uint8_t>& pixels);
		// TODO: move/copy constructor
		virtual ~ImageData() = default;

		bool isValid() const noexcept;

		static std::shared_ptr<ImageData> readFromFile(
			const std::string& filePath,
			bool component16);
	};
}