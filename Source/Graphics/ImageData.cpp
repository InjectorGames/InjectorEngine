#include "Injector/Graphics/ImageData.hpp"
#include "Injector/Exception/Exception.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Injector
{
	ImageData::ImageData() :
		size(),
		componentCount(),
		component16(),
		pixels()
	{
	}
	ImageData::ImageData(
		const SizeVector3& _size,
		int _componentCount,
		bool _component16,
		const std::vector<uint8_t>& _pixels) :
		size(_size),
		componentCount(_componentCount),
		component16(_component16),
		pixels(_pixels)
	{
	}

	bool ImageData::isValid() const noexcept
	{
		if(componentCount < 1 || componentCount > 4)
			return false;

		if(component16)
			return size.x * size.y * componentCount * 2 == pixels.size();
		else
			return size.x * size.y * componentCount == pixels.size();
	}

	std::shared_ptr<ImageData> ImageData::readFromFile(
		const std::string& filePath,
		int componentCount,
		bool component16)
	{
		void* data;
		int width, height;

		if (component16)
		{
			data = stbi_load_16(
				filePath.c_str(),
				&width,
				&height,
				&componentCount,
				componentCount);
		}
		else
		{
			data = stbi_load(
				filePath.c_str(),
				&width,
				&height,
				&componentCount,
				componentCount);
		}

		if (!data || width < 1 || height < 1)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to load image, " +
					std::string(stbi_failure_reason()));
		}

		auto imageData = std::make_shared<ImageData>(
			SizeVector3(
				width,
				height,
				1),
			componentCount,
			component16,
			std::vector<uint8_t>());

		auto binarySize = component16 ?
			width * height * componentCount * 2 :
			width * height * componentCount;
		imageData->pixels = std::vector<uint8_t>(binarySize);

		memcpy(
			imageData->pixels.data(),
			data,
			binarySize);

		stbi_image_free(data);
		return imageData;
	}
}
