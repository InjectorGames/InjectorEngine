#pragma once
#include "Injector/Mathematics/IntVector2.hpp"
#include <string>

namespace Injector::Graphics
{
	using namespace std;
	using namespace Injector::Mathematics;

	class Image
	{
	protected:
		int channelCount;
		IntVector2 size;
		unsigned char* data;
	public:
		Image(const string& filePath,
			int channelCount = 0);
		virtual ~Image();
	};
}