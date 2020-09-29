#pragma once
#include "Injector/Memory/MemoryStream.hpp"

namespace Injector
{
	class Datagram
	{
	 public:
		virtual ~Datagram() = default;

		virtual size_t getSize() const = 0;
		virtual void toBytes(MemoryStream& stream) const = 0;
		virtual void fromBytes(MemoryStream& stream) = 0;
	};
}
