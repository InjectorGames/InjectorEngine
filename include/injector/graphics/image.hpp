#pragma once
#include "Injector/Mathematics/IntVector2.hpp"
#include <string>

namespace Injector
{
	class Image
	{
	protected:
		int channelCount;
		IntVector2 size;
		unsigned char* data;
	public:
		Image(const std::string& filePath,
			int channelCount = 0);
		virtual ~Image();
	};
}