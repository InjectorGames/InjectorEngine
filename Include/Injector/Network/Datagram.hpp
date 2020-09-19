#pragma once
#include "Injector/Memory/MemoryStream.hpp"

namespace Injector
{
	class Datagram
	{
	 public:
		virtual ~Datagram();
		virtual size_t getSize() const;
		virtual void toBytes(MemoryStream& stream) const;
		virtual void fromBytes(MemoryStream& stream);
	};
}
