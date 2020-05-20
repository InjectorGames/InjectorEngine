#pragma once
#include <inject/memory_stream.hpp>

namespace inject
{
	struct UdpRequestResponse
	{
		inline static constexpr size_t headerSize = 1;

		inline void toBytes(void* const buffer, const size_t size) const
		{
			toBytes(MemoryStream(buffer, size));
		}
		inline void fromBytes(const void* const buffer, const size_t size)
		{
			fromBytes(MemoryStream(buffer, size));
		}

		virtual const size_t getSize() const = 0;
		virtual void toBytes(Stream& stream) const = 0;
		virtual void fromBytes(Stream& stream) = 0;
	};
}
