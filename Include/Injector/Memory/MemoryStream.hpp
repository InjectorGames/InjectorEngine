#pragma once
#include <sstream>

namespace Injector
{
	class MemoryStream : public std::stringstream
	{
	 public:
		MemoryStream(
			const std::string& string,
			const std::ios::openmode mode =
				ios_base::in | ios_base::out);
		virtual ~MemoryStream();

		std::istream& read(char& value);
		std::istream& read(char* values, size_t count);
		std::istream& read(uint8_t& value);
		std::istream& read(uint8_t* values, size_t count);
		std::istream& read(int8_t& value);
		std::istream& read(int8_t* values, size_t count);
		std::istream& read(uint16_t& value);
		std::istream& read(uint16_t* values, size_t count);
		std::istream& read(int16_t& value);
		std::istream& read(int16_t* values, size_t count);
		std::istream& read(uint32_t& value);
		std::istream& read(uint32_t* values, size_t count);
		std::istream& read(int32_t& value);
		std::istream& read(int32_t* values, size_t count);
		std::istream& read(uint64_t& value);
		std::istream& read(uint64_t* values, size_t count);
		std::istream& read(int64_t& value);
		std::istream& read(int64_t* values, size_t count);
		std::istream& read(float& value);
		std::istream& read(float* values, size_t count);
		std::istream& read(double& value);
		std::istream& read(double* values, size_t count);

		std::istream& readBigEndian(uint16_t& value);
		std::istream& readBigEndian(int16_t& value);
		std::istream& readBigEndian(uint32_t& value);
		std::istream& readBigEndian(int32_t& value);
		std::istream& readBigEndian(uint64_t& value);
		std::istream& readBigEndian(int64_t& value);
		std::istream& readBigEndian(float& value);
		std::istream& readBigEndian(double& value);

		std::istream& readLittleEndian(uint16_t& value);
		std::istream& readLittleEndian(int16_t& value);
		std::istream& readLittleEndian(uint32_t& value);
		std::istream& readLittleEndian(int32_t& value);
		std::istream& readLittleEndian(uint64_t& value);
		std::istream& readLittleEndian(int64_t& value);
		std::istream& readLittleEndian(float& value);
		std::istream& readLittleEndian(double& value);

		std::ostream& write(char value);
		std::ostream& write(const char* value, size_t count);
		std::ostream& write(uint8_t value);
		std::ostream& write(const uint8_t* value, size_t count);
		std::ostream& write(int8_t value);
		std::ostream& write(const int8_t* value, size_t count);
		std::ostream& write(uint16_t value);
		std::ostream& write(const uint16_t* value, size_t count);
		std::ostream& write(int16_t value);
		std::ostream& write(const int16_t* value, size_t count);
		std::ostream& write(uint32_t value);
		std::ostream& write(const uint32_t* value, size_t count);
		std::ostream& write(int32_t value);
		std::ostream& write(const int32_t* value, size_t count);
		std::ostream& write(uint64_t value);
		std::ostream& write(const uint64_t* value, size_t count);
		std::ostream& write(int64_t value);
		std::ostream& write(const int64_t* value, size_t count);
		std::ostream& write(float value);
		std::ostream& write(const float* value, size_t count);
		std::ostream& write(double value);
		std::ostream& write(const double* value, size_t count);

		std::ostream& writeBigEndian(uint16_t value);
		std::ostream& writeBigEndian(int16_t value);
		std::ostream& writeBigEndian(uint32_t value);
		std::ostream& writeBigEndian(int32_t value);
		std::ostream& writeBigEndian(uint64_t value);
		std::ostream& writeBigEndian(int64_t value);
		std::ostream& writeBigEndian(float value);
		std::ostream& writeBigEndian(double value);

		std::ostream& writeLittleEndian(uint16_t value);
		std::ostream& writeLittleEndian(int16_t value);
		std::ostream& writeLittleEndian(uint32_t value);
		std::ostream& writeLittleEndian(int32_t value);
		std::ostream& writeLittleEndian(uint64_t value);
		std::ostream& writeLittleEndian(int64_t value);
		std::ostream& writeLittleEndian(float value);
		std::ostream& writeLittleEndian(double value);
	};
}
