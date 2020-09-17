#include "Injector/Graphics/Image.hpp"
#include "Injector/Exception/Exception.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Injector
{
	Image::Image(
		const std::string& filePath,
		int _channelCount)
	{
		stbi_set_flip_vertically_on_load(true);
		data = stbi_load(filePath.c_str(), &size.x, &size.y, &channelCount, _channelCount);

		if(!data)
			throw Exception("Image", "Image", "Failed to load image");
	}
	Image::~Image()
	{
		stbi_image_free(data);
	}

	const IntVector2& Image::getSize() const noexcept
	{
		return size;
	}
	uint8_t* Image::getData() const noexcept
	{
		return data;
	}
	int Image::getChannelCount() const noexcept
	{
		return channelCount;
	}
}
