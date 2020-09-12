#include "Injector/Graphics/Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Injector
{
	Image::Image(
		const IntVector2& _size,
		uint8_t* _data,
		int _channelCount) :
		size(_size),
		data(_data),
		channelCount(_channelCount)
	{}
	Image::Image(
		const std::string& filePath,
		int _channelCount)
	{
		data = stbi_load(filePath.c_str(), &size.x, &size.y, &channelCount, _channelCount);
	}
	Image::~Image()
	{
		stbi_image_free(data);
	}

	const IntVector2& Image::getSize() const noexcept
	{
		return size;
	}
	const uint8_t* Image::getData() const noexcept
	{
		return data;
	}
	int Image::getChannelCount() const noexcept
	{
		return channelCount;
	}
}
