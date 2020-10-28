#pragma once
#include <cstdint>
#include <cstdlib>

namespace Injector
{
	// Network message storage class
	class Datagram
	{
	 protected:
		// Datagram type value
		uint8_t type;
		// Is datagram data valid
		bool valid;
	 public:
		// Creates a new datagram
		explicit Datagram(uint8_t type);
		// Destroys datagram
		virtual ~Datagram() = default;

		// Returns datagram type
		uint8_t getType() const noexcept;
		// Returns true if datagram data is valid
		bool isValid() const noexcept;

		// Returns datagram data binary size
		virtual size_t getByteSize() const = 0;
		// Reads datagram data from the buffer
		virtual void readData(
			const uint8_t* buffer,
			size_t byteCount) = 0;
		// Writes datagram data to the buffer
		virtual void writeData(
			uint8_t* buffer) const = 0;
	};
}
