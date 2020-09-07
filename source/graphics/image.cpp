#include "Injector/Graphics/Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Injector
{
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
}
