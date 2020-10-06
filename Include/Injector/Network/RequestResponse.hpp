#pragma once
#include "Injector/Memory/MemoryStream.hpp"

namespace Injector
{
	class RequestResponse
	{
	 public:
		// Destroys request/response
		virtual ~RequestResponse() = default;

		// Returns request/response type
		virtual uint8_t getType() const = 0;
		// Returns request/response data size
		virtual size_t getDataSize() const = 0;

		// Writes request/response data to the stream
		virtual void writeData(
			MemoryStream& stream) const = 0;
		// Reads request/response data from the stream
		virtual void readData(
			MemoryStream& stream) = 0;
	};
}
