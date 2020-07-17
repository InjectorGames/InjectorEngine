#pragma once
#include <inject/memory_stream.hpp>
#include <vector>

namespace INJECT_NAMESPACE
{
	struct Datagram
	{
		inline static constexpr size_t headerSize = 1;

		virtual const size_t getSize() const = 0;
		virtual void toBytes(MemoryStream& stream) const = 0;
		virtual void fromBytes(MemoryStream& stream) = 0;
	};
}
