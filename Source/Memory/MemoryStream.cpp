#include "Injector/Memory/MemoryStream.hpp"
#include "Injector/Memory/ByteSwap.hpp"

namespace Injector
{
	MemoryStream::MemoryStream(
		const std::string& string,
		const std::ios::openmode mode) :
		std::stringstream(string, mode)
	{
	}

	std::istream& MemoryStream::read(char& value)
	{
		return std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(char));
	}
	std::istream& MemoryStream::read(char* values, size_t count)
	{
		return std::stringstream::read(
			reinterpret_cast<char*>(values), sizeof(char) * count);
	}
	std::istream& MemoryStream::read(uint8_t& value)
	{
		return std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(uint8_t));
	}
	std::istream& MemoryStream::read(uint8_t* values, size_t count)
	{
		return std::stringstream::read(
			reinterpret_cast<char*>(values), sizeof(uint8_t) * count);
	}
	std::istream& MemoryStream::read(int8_t& value)
	{
		return std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(int8_t));
	}
	std::istream& MemoryStream::read(int8_t* values, size_t count)
	{
		return std::stringstream::read(
			reinterpret_cast<char*>(values), sizeof(int8_t) * count);
	}
	std::istream& MemoryStream::read(uint16_t& value)
	{
		return std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(uint16_t));
	}
	std::istream& MemoryStream::read(uint16_t* values, size_t count)
	{
		return std::stringstream::read(
			reinterpret_cast<char*>(values), sizeof(uint16_t) * count);
	}
	std::istream& MemoryStream::read(int16_t& value)
	{
		return std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(int16_t));
	}
	std::istream& MemoryStream::read(int16_t* values, size_t count)
	{
		return std::stringstream::read(
			reinterpret_cast<char*>(values), sizeof(int16_t) * count);
	}
	std::istream& MemoryStream::read(uint32_t& value)
	{
		return std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(uint32_t));
	}
	std::istream& MemoryStream::read(uint32_t* values, size_t count)
	{
		return std::stringstream::read(
			reinterpret_cast<char*>(values), sizeof(uint32_t) * count);
	}
	std::istream& MemoryStream::read(int32_t& value)
	{
		return std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(int32_t));
	}
	std::istream& MemoryStream::read(int32_t* values, size_t count)
	{
		return std::stringstream::read(
			reinterpret_cast<char*>(values), sizeof(int32_t) * count);
	}
	std::istream& MemoryStream::read(uint64_t& value)
	{
		return std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(uint64_t));
	}
	std::istream& MemoryStream::read(uint64_t* values, size_t count)
	{
		return std::stringstream::read(
			reinterpret_cast<char*>(values), sizeof(uint64_t) * count);
	}
	std::istream& MemoryStream::read(int64_t& value)
	{
		return std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(int64_t));
	}
	std::istream& MemoryStream::read(int64_t* values, size_t count)
	{
		return std::stringstream::read(
			reinterpret_cast<char*>(values), sizeof(int64_t) * count);
	}
	std::istream& MemoryStream::read(float& value)
	{
		return std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(float));
	}
	std::istream& MemoryStream::read(float* values, size_t count)
	{
		return std::stringstream::read(
			reinterpret_cast<char*>(values), sizeof(float) * count);
	}
	std::istream& MemoryStream::read(double& value)
	{
		return std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(double));
	}
	std::istream& MemoryStream::read(double* values, size_t count)
	{
		return std::stringstream::read(
			reinterpret_cast<char*>(values), sizeof(double) * count);
	}

	std::istream& MemoryStream::readBigEndian(uint16_t& value)
	{
		auto& stream = std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(uint16_t));

		value = ByteSwap::swapBigEndian(value);
		return stream;
	}
	std::istream& MemoryStream::readBigEndian(int16_t& value)
	{
		auto& stream = std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(int16_t));

		value = ByteSwap::swapBigEndian(value);
		return stream;
	}
	std::istream& MemoryStream::readBigEndian(uint32_t& value)
	{
		auto& stream = std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(uint32_t));

		value = ByteSwap::swapBigEndian(value);
		return stream;
	}
	std::istream& MemoryStream::readBigEndian(int32_t& value)
	{
		auto& stream = std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(int32_t));

		value = ByteSwap::swapBigEndian(value);
		return stream;
	}
	std::istream& MemoryStream::readBigEndian(uint64_t& value)
	{
		auto& stream = std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(uint64_t));

		value = ByteSwap::swapBigEndian(value);
		return stream;
	}
	std::istream& MemoryStream::readBigEndian(int64_t& value)
	{
		auto& stream = std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(int64_t));

		value = ByteSwap::swapBigEndian(value);
		return stream;
	}
	std::istream& MemoryStream::readBigEndian(float& value)
	{
		auto& stream = std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(float));

		value = ByteSwap::swapBigEndian(value);
		return stream;
	}
	std::istream& MemoryStream::readBigEndian(double& value)
	{
		auto& stream = std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(double));

		value = ByteSwap::swapBigEndian(value);
		return stream;
	}

	std::istream& MemoryStream::readLittleEndian(uint16_t& value)
	{
		auto& stream = std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(uint16_t));

		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}
	std::istream& MemoryStream::readLittleEndian(int16_t& value)
	{
		auto& stream = std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(int16_t));

		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}
	std::istream& MemoryStream::readLittleEndian(uint32_t& value)
	{
		auto& stream = std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(uint32_t));

		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}
	std::istream& MemoryStream::readLittleEndian(int32_t& value)
	{
		auto& stream = std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(int32_t));

		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}
	std::istream& MemoryStream::readLittleEndian(uint64_t& value)
	{
		auto& stream = std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(uint64_t));

		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}
	std::istream& MemoryStream::readLittleEndian(int64_t& value)
	{
		auto& stream = std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(int64_t));

		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}
	std::istream& MemoryStream::readLittleEndian(float& value)
	{
		auto& stream = std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(float));

		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}
	std::istream& MemoryStream::readLittleEndian(double& value)
	{
		auto& stream = std::stringstream::read(
			reinterpret_cast<char*>(&value), sizeof(double));

		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}

	std::ostream& MemoryStream::write(char value)
	{
		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(char));
	}
	std::ostream& MemoryStream::write(const char* values, size_t count)
	{
		return std::stringstream::write(
			reinterpret_cast<const char*>(values), sizeof(char) * count);
	}
	std::ostream& MemoryStream::write(uint8_t value)
	{
		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(uint8_t));
	}
	std::ostream& MemoryStream::write(const uint8_t* values, size_t count)
	{
		return std::stringstream::write(
			reinterpret_cast<const char*>(values), sizeof(uint8_t) * count);
	}
	std::ostream& MemoryStream::write(int8_t value)
	{
		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(int8_t));
	}
	std::ostream& MemoryStream::write(const int8_t* values, size_t count)
	{
		return std::stringstream::write(
			reinterpret_cast<const char*>(values), sizeof(int8_t) * count);
	}
	std::ostream& MemoryStream::write(uint16_t value)
	{
		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(uint16_t));
	}
	std::ostream& MemoryStream::write(const uint16_t* values, size_t count)
	{
		return std::stringstream::write(
			reinterpret_cast<const char*>(values), sizeof(uint16_t) * count);
	}
	std::ostream& MemoryStream::write(int16_t value)
	{
		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(int16_t));
	}
	std::ostream& MemoryStream::write(const int16_t* values, size_t count)
	{
		return std::stringstream::write(
			reinterpret_cast<const char*>(values), sizeof(int16_t) * count);
	}
	std::ostream& MemoryStream::write(uint32_t value)
	{
		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(uint32_t));
	}
	std::ostream& MemoryStream::write(const uint32_t* values, size_t count)
	{
		return std::stringstream::write(
			reinterpret_cast<const char*>(values), sizeof(uint32_t) * count);
	}
	std::ostream& MemoryStream::write(int32_t value)
	{
		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(int32_t));
	}
	std::ostream& MemoryStream::write(const int32_t* values, size_t count)
	{
		return std::stringstream::write(
			reinterpret_cast<const char*>(values), sizeof(int32_t) * count);
	}
	std::ostream& MemoryStream::write(uint64_t value)
	{
		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(uint64_t));
	}
	std::ostream& MemoryStream::write(const uint64_t* values, size_t count)
	{
		return std::stringstream::write(
			reinterpret_cast<const char*>(values), sizeof(uint64_t) * count);
	}
	std::ostream& MemoryStream::write(int64_t value)
	{
		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(int64_t));
	}
	std::ostream& MemoryStream::write(const int64_t* values, size_t count)
	{
		return std::stringstream::write(
			reinterpret_cast<const char*>(values), sizeof(int64_t) * count);
	}
	std::ostream& MemoryStream::write(float value)
	{
		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(float));
	}
	std::ostream& MemoryStream::write(const float* values, size_t count)
	{
		return std::stringstream::write(
			reinterpret_cast<const char*>(values), sizeof(float) * count);
	}
	std::ostream& MemoryStream::write(double value)
	{
		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(double));
	}
	std::ostream& MemoryStream::write(const double* values, size_t count)
	{
		return std::stringstream::write(
			reinterpret_cast<const char*>(values), sizeof(double) * count);
	}

	std::ostream& MemoryStream::writeBigEndian(uint16_t value)
	{
		value = ByteSwap::swapBigEndian(value);

		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(uint16_t));
	}
	std::ostream& MemoryStream::writeBigEndian(int16_t value)
	{
		value = ByteSwap::swapBigEndian(value);

		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(int16_t));
	}
	std::ostream& MemoryStream::writeBigEndian(uint32_t value)
	{
		value = ByteSwap::swapBigEndian(value);

		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(uint32_t));
	}
	std::ostream& MemoryStream::writeBigEndian(int32_t value)
	{
		value = ByteSwap::swapBigEndian(value);

		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(int32_t));
	}
	std::ostream& MemoryStream::writeBigEndian(uint64_t value)
	{
		value = ByteSwap::swapBigEndian(value);

		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(uint64_t));
	}
	std::ostream& MemoryStream::writeBigEndian(int64_t value)
	{
		value = ByteSwap::swapBigEndian(value);

		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(int64_t));
	}
	std::ostream& MemoryStream::writeBigEndian(float value)
	{
		value = ByteSwap::swapBigEndian(value);

		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(float));
	}
	std::ostream& MemoryStream::writeBigEndian(double value)
	{
		value = ByteSwap::swapBigEndian(value);

		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(double));
	}

	std::ostream& MemoryStream::writeLittleEndian(uint16_t value)
	{
		value = ByteSwap::swapLittleEndian(value);

		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(uint16_t));
	}
	std::ostream& MemoryStream::writeLittleEndian(int16_t value)
	{
		value = ByteSwap::swapLittleEndian(value);

		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(int16_t));
	}
	std::ostream& MemoryStream::writeLittleEndian(uint32_t value)
	{
		value = ByteSwap::swapLittleEndian(value);

		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(uint32_t));
	}
	std::ostream& MemoryStream::writeLittleEndian(int32_t value)
	{
		value = ByteSwap::swapLittleEndian(value);

		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(int32_t));
	}
	std::ostream& MemoryStream::writeLittleEndian(uint64_t value)
	{
		value = ByteSwap::swapLittleEndian(value);

		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(uint64_t));
	}
	std::ostream& MemoryStream::writeLittleEndian(int64_t value)
	{
		value = ByteSwap::swapLittleEndian(value);

		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(int64_t));
	}
	std::ostream& MemoryStream::writeLittleEndian(float value)
	{
		value = ByteSwap::swapLittleEndian(value);

		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(float));
	}
	std::ostream& MemoryStream::writeLittleEndian(double value)
	{
		value = ByteSwap::swapLittleEndian(value);

		return std::stringstream::write(
			reinterpret_cast<const char*>(&value), sizeof(double));
	}
}
