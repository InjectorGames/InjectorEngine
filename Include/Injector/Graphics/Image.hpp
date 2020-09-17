#pragma once
#include "Injector/Mathematics/IntVector2.hpp"

#include <string>
#include <cstdint>

namespace Injector
{
	class Image
	{
	protected:
		IntVector2 size;
		uint8_t* data;
		int channelCount;
	public:
		Image(const std::string& filePath,
			int channelCount = 0);
		virtual ~Image();

		const IntVector2& getSize() const noexcept;
		uint8_t* getData() const noexcept;
		int getChannelCount() const noexcept;
	};
}