#pragma once
#include <inject/memory_stream.hpp>

namespace inject
{
	struct UdpRequestResponse
	{
		inline static constexpr size_t headerSize = 1;

		inline void toBytes(void* const buffer, const size_t size) const
		{
			if (toBytes(MemoryStream(buffer, size)) != size)
				throw std::runtime_error("Failed to write bytes");
		}
		inline void fromBytes(const void* const buffer, const size_t size)
		{
			if (fromBytes(MemoryStream(buffer, size)) != size)
				throw std::runtime_error("Failed to read bytes");
		}

		virtual const size_t getSize() const = 0;
		virtual const size_t toBytes(Stream& stream) const = 0;
		virtual const size_t fromBytes(Stream& stream) = 0;
	};
}
