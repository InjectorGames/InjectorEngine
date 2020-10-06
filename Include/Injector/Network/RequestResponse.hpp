#pragma once
#include <cstdint>
#include <cstdlib>

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

		// Writes request/response data to the buffer
		virtual void writeData(void* buffer) const = 0;
		// Reads request/response data from the buffer
		virtual void readData(const void* buffer) = 0;
	};
}
