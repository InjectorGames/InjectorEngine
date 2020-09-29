#pragma once
#include "Injector/Mathematics/IntVector2.hpp"

#include <vector>
#include <string>
#include <cstdint>
#include <memory>

namespace Injector
{
	struct ImageData
	{
		IntVector2 size;
		int componentCount;
		bool component16;
		std::vector<uint8_t> pixels;

		ImageData();
		ImageData(
			const IntVector2& size,
			int componentCount,
			bool component16,
			const std::vector<uint8_t>& pixels);
		virtual ~ImageData() = default;

		bool isValid() const noexcept;

		static std::shared_ptr<ImageData> readFromFile(
			const std::string& filePath,
			int componentCount,
			bool component16);
	};
}