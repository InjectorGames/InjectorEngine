#pragma once
#include <vector>
#include <cstdint>
#include <cstdlib>

namespace Injector
{
	class RequestResponse
	{
	 public:
		// Destroys request/response
		virtual ~RequestResponse() = default;

		// Returns request/response byte data size
		virtual size_t getByteSize() const = 0;

		// Returns true if request/response byte data writen to the buffer
		virtual bool writeBytes(
			uint8_t* buffer,
			size_t byteCount) const = 0;
		// Returns true if request/response byte data read from the buffer
		virtual bool readBytes(
			const uint8_t* buffer,
			size_t byteCount) = 0;
	};
}
