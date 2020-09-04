#pragma once
#include <injector/mathematics/int_vector2.hpp>
#include <string>

namespace injector::graphics
{
	class Image
	{
	protected:
		int channelCount;
		IntVector2 size;
		unsigned char* data;
	public:
		Image(
			const std::string& filePath,
			int channelCount = 0);
		virtual ~Image();
	};
}