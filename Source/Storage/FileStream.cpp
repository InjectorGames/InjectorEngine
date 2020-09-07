#include "Injector/Storage/FileStream.hpp"
#include "Injector/Storage/FileException.hpp"
#include "Injector/Memory/ByteSwap.hpp"

namespace Injector
{
	FileStream::FileStream() :
		std::fstream()
	{}
	FileStream::FileStream(const char* filePath, std::ios::openmode mode) :
		std::fstream(filePath, mode)
	{
		if(!is_open())
			throw FileException("Failed to open file", std::string(filePath));
	}
	FileStream::FileStream(const std::string& filePath, std::ios::openmode mode) :
		std::fstream(filePath, mode)
	{
		if(!is_open())
			throw FileException("Failed to open file", filePath);
	}
	FileStream::~FileStream()
	{}

	std::istream& FileStream::read(char& value)
	{
		return std::fstream::read(reinterpret_cast<char*>(&value), sizeof(char));
	}
	std::istream& FileStream::read(char* value, size_t count)
	{
		return std::fstream::read(reinterpret_cast<char*>(value), sizeof(char) * count);
	}
	std::istream& FileStream::read(uint8_t& value)
	{
		return std::fstream::read(reinterpret_cast<char*>(&value), sizeof(uint8_t));
	}
	std::istream& FileStream::read(uint8_t* value, size_t count)
	{
		return std::fstream::read(reinterpret_cast<char*>(value), sizeof(uint8_t) * count);
	}
	std::istream& FileStream::read(int8_t& value)
	{
		return std::fstream::read(reinterpret_cast<char*>(&value), sizeof(int8_t));
	}
	std::istream& FileStream::read(int8_t* value, size_t count)
	{
		return std::fstream::read(reinterpret_cast<char*>(value), sizeof(int8_t) * count);
	}
	std::istream& FileStream::read(uint16_t& value)
	{
		return std::fstream::read(reinterpret_cast<char*>(&value), sizeof(uint16_t));
	}
	std::istream& FileStream::read(uint16_t* value, size_t count)
	{
		return std::fstream::read(reinterpret_cast<char*>(value), sizeof(uint16_t) * count);
	}
	std::istream& FileStream::read(int16_t& value)
	{
		return std::fstream::read(reinterpret_cast<char*>(&value), sizeof(int16_t));
	}
	std::istream& FileStream::read(int16_t* value, size_t count)
	{
		return std::fstream::read(reinterpret_cast<char*>(value), sizeof(int16_t) * count);
	}
	std::istream& FileStream::read(uint32_t& value)
	{
		return std::fstream::read(reinterpret_cast<char*>(&value), sizeof(uint32_t));
	}
	std::istream& FileStream::read(uint32_t* value, size_t count)
	{
		return std::fstream::read(reinterpret_cast<char*>(value), sizeof(uint32_t) * count);
	}
	std::istream& FileStream::read(int32_t& value)
	{
		return std::fstream::read(reinterpret_cast<char*>(&value), sizeof(int32_t));
	}
	std::istream& FileStream::read(int32_t* value, size_t count)
	{
		return std::fstream::read(reinterpret_cast<char*>(value), sizeof(int32_t) * count);
	}
	std::istream& FileStream::read(uint64_t& value)
	{
		return std::fstream::read(reinterpret_cast<char*>(&value), sizeof(uint64_t));
	}
	std::istream& FileStream::read(uint64_t* value, size_t count)
	{
		return std::fstream::read(reinterpret_cast<char*>(value), sizeof(uint64_t) * count);
	}
	std::istream& FileStream::read(int64_t& value)
	{
		return std::fstream::read(reinterpret_cast<char*>(&value), sizeof(int64_t));
	}
	std::istream& FileStream::read(int64_t* value, size_t count)
	{
		return std::fstream::read(reinterpret_cast<char*>(value), sizeof(int64_t) * count);
	}
	std::istream& FileStream::read(float& value)
	{
		return std::fstream::read(reinterpret_cast<char*>(&value), sizeof(float));
	}
	std::istream& FileStream::read(float* value, size_t count)
	{
		return std::fstream::read(reinterpret_cast<char*>(value), sizeof(float) * count);
	}
	std::istream& FileStream::read(double& value)
	{
		return std::fstream::read(reinterpret_cast<char*>(&value), sizeof(double));
	}
	std::istream& FileStream::read(double* value, size_t count)
	{
		return std::fstream::read(reinterpret_cast<char*>(value), sizeof(double) * count);
	}

	std::istream& FileStream::readBE(uint16_t& value)
	{
		auto& stream = std::fstream::read(reinterpret_cast<char*>(&value), sizeof(uint16_t));
		value = ByteSwap::swapBigEndian(value);
		return stream;
	}
	std::istream& FileStream::readBE(int16_t& value)
	{
		auto& stream = std::fstream::read(reinterpret_cast<char*>(&value), sizeof(int16_t));
		value = ByteSwap::swapBigEndian(value);
		return stream;
	}
	std::istream& FileStream::readBE(uint32_t& value)
	{
		auto& stream = std::fstream::read(reinterpret_cast<char*>(&value), sizeof(uint32_t));
		value = ByteSwap::swapBigEndian(value);
		return stream;
	}
	std::istream& FileStream::readBE(int32_t& value)
	{
		auto& stream = std::fstream::read(reinterpret_cast<char*>(&value), sizeof(int32_t));
		value = ByteSwap::swapBigEndian(value);
		return stream;
	}
	std::istream& FileStream::readBE(uint64_t& value)
	{
		auto& stream = std::fstream::read(reinterpret_cast<char*>(&value), sizeof(uint64_t));
		value = ByteSwap::swapBigEndian(value);
		return stream;
	}
	std::istream& FileStream::readBE(int64_t& value)
	{
		auto& stream = std::fstream::read(reinterpret_cast<char*>(&value), sizeof(int64_t));
		value = ByteSwap::swapBigEndian(value);
		return stream;
	}
	std::istream& FileStream::readBE(float& value)
	{
		auto& stream = std::fstream::read(reinterpret_cast<char*>(&value), sizeof(float));
		value = ByteSwap::swapBigEndian(value);
		return stream;
	}
	std::istream& FileStream::readBE(double& value)
	{
		auto& stream = std::fstream::read(reinterpret_cast<char*>(&value), sizeof(double));
		value = ByteSwap::swapBigEndian(value);
		return stream;
	}

	std::istream& FileStream::readLE(uint16_t& value)
	{
		auto& stream = std::fstream::read(reinterpret_cast<char*>(&value), sizeof(uint16_t));
		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}
	std::istream& FileStream::readLE(int16_t& value)
	{
		auto& stream = std::fstream::read(reinterpret_cast<char*>(&value), sizeof(int16_t));
		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}
	std::istream& FileStream::readLE(uint32_t& value)
	{
		auto& stream = std::fstream::read(reinterpret_cast<char*>(&value), sizeof(uint32_t));
		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}
	std::istream& FileStream::readLE(int32_t& value)
	{
		auto& stream = std::fstream::read(reinterpret_cast<char*>(&value), sizeof(int32_t));
		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}
	std::istream& FileStream::readLE(uint64_t& value)
	{
		auto& stream = std::fstream::read(reinterpret_cast<char*>(&value), sizeof(uint64_t));
		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}
	std::istream& FileStream::readLE(int64_t& value)
	{
		auto& stream = std::fstream::read(reinterpret_cast<char*>(&value), sizeof(int64_t));
		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}
	std::istream& FileStream::readLE(float& value)
	{
		auto& stream = std::fstream::read(reinterpret_cast<char*>(&value), sizeof(float));
		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}
	std::istream& FileStream::readLE(double& value)
	{
		auto& stream = std::fstream::read(reinterpret_cast<char*>(&value), sizeof(double));
		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}

	std::ostream& FileStream::write(char value)
	{
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(char));
	}
	std::ostream& FileStream::write(const char* value, size_t count)
	{
		return std::fstream::write(reinterpret_cast<const char*>(value), sizeof(char) * count);
	}
	std::ostream& FileStream::write(uint8_t value)
	{
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(uint8_t));
	}
	std::ostream& FileStream::write(const uint8_t* value, size_t count)
	{
		return std::fstream::write(reinterpret_cast<const char*>(value), sizeof(uint8_t) * count);
	}
	std::ostream& FileStream::write(int8_t value)
	{
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(int8_t));
	}
	std::ostream& FileStream::write(const int8_t* value, size_t count)
	{
		return std::fstream::write(reinterpret_cast<const char*>(value), sizeof(int8_t) * count);
	}
	std::ostream& FileStream::write(uint16_t value)
	{
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(uint16_t));
	}
	std::ostream& FileStream::write(const uint16_t* value, size_t count)
	{
		return std::fstream::write(reinterpret_cast<const char*>(value), sizeof(uint16_t) * count);
	}
	std::ostream& FileStream::write(int16_t value)
	{
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(int16_t));
	}
	std::ostream& FileStream::write(const int16_t* value, size_t count)
	{
		return std::fstream::write(reinterpret_cast<const char*>(value), sizeof(int16_t) * count);
	}
	std::ostream& FileStream::write(uint32_t value)
	{
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(uint32_t));
	}
	std::ostream& FileStream::write(const uint32_t* value, size_t count)
	{
		return std::fstream::write(reinterpret_cast<const char*>(value), sizeof(uint32_t) * count);
	}
	std::ostream& FileStream::write(int32_t value)
	{
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(int32_t));
	}
	std::ostream& FileStream::write(const int32_t* value, size_t count)
	{
		return std::fstream::write(reinterpret_cast<const char*>(value), sizeof(int32_t) * count);
	}
	std::ostream& FileStream::write(uint64_t value)
	{
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(uint64_t));
	}
	std::ostream& FileStream::write(const uint64_t* value, size_t count)
	{
		return std::fstream::write(reinterpret_cast<const char*>(value), sizeof(uint64_t) * count);
	}
	std::ostream& FileStream::write(int64_t value)
	{
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(int64_t));
	}
	std::ostream& FileStream::write(const int64_t* value, size_t count)
	{
		return std::fstream::write(reinterpret_cast<const char*>(value), sizeof(int64_t) * count);
	}
	std::ostream& FileStream::write(float value)
	{
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(float));
	}
	std::ostream& FileStream::write(const float* value, size_t count)
	{
		return std::fstream::write(reinterpret_cast<const char*>(value), sizeof(float) * count);
	}
	std::ostream& FileStream::write(double value)
	{
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(double));
	}
	std::ostream& FileStream::write(const double* value, size_t count)
	{
		return std::fstream::write(reinterpret_cast<const char*>(value), sizeof(double) * count);
	}

	std::ostream& FileStream::writeBE(uint16_t value)
	{
		value = ByteSwap::swapBigEndian(value);
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(uint16_t));
	}
	std::ostream& FileStream::writeBE(int16_t value)
	{
		value = ByteSwap::swapBigEndian(value);
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(int16_t));
	}
	std::ostream& FileStream::writeBE(uint32_t value)
	{
		value = ByteSwap::swapBigEndian(value);
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(uint32_t));
	}
	std::ostream& FileStream::writeBE(int32_t value)
	{
		value = ByteSwap::swapBigEndian(value);
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(int32_t));
	}
	std::ostream& FileStream::writeBE(uint64_t value)
	{
		value = ByteSwap::swapBigEndian(value);
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(uint64_t));
	}
	std::ostream& FileStream::writeBE(int64_t value)
	{
		value = ByteSwap::swapBigEndian(value);
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(int64_t));
	}
	std::ostream& FileStream::writeBE(float value)
	{
		value = ByteSwap::swapBigEndian(value);
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(float));
	}
	std::ostream& FileStream::writeBE(double value)
	{
		value = ByteSwap::swapBigEndian(value);
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(double));
	}

	std::ostream& FileStream::writeLE(uint16_t value)
	{
		value = ByteSwap::swapLittleEndian(value);
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(uint16_t));
	}
	std::ostream& FileStream::writeLE(int16_t value)
	{
		value = ByteSwap::swapLittleEndian(value);
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(int16_t));
	}
	std::ostream& FileStream::writeLE(uint32_t value)
	{
		value = ByteSwap::swapLittleEndian(value);
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(uint32_t));
	}
	std::ostream& FileStream::writeLE(int32_t value)
	{
		value = ByteSwap::swapLittleEndian(value);
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(int32_t));
	}
	std::ostream& FileStream::writeLE(uint64_t value)
	{
		value = ByteSwap::swapLittleEndian(value);
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(uint64_t));
	}
	std::ostream& FileStream::writeLE(int64_t value)
	{
		value = ByteSwap::swapLittleEndian(value);
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(int64_t));
	}
	std::ostream& FileStream::writeLE(float value)
	{
		value = ByteSwap::swapLittleEndian(value);
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(float));
	}
	std::ostream& FileStream::writeLE(double value)
	{
		value = ByteSwap::swapLittleEndian(value);
		return std::fstream::write(reinterpret_cast<const char*>(&value), sizeof(double));
	}

	std::string FileStream::readAllText(
		const std::string& filePath)
	{
		auto fileStream = FileStream(filePath, std::ios::in | std::ios::ate);

		auto size = static_cast<size_t>(fileStream.tellg());
		fileStream.seekg(0, fileStream.beg);

		auto text = std::string(size, ' ');
		fileStream.read(text.data(), size);

		return text;
	}
	void FileStream::writeAllText(
		const std::string& filePath,
		const char* text,
		size_t count)
	{
		auto fileStream = FileStream(filePath, std::ios::out);
		fileStream.write(text, count);
	}
	void FileStream::writeAllText(
		const std::string& filePath,
		const std::string& text)
	{
		auto fileStream = FileStream(filePath, std::ios::out);
		fileStream.write(text.data(), text.size());
	}
	
	std::vector<char> FileStream::readAllBytes(
		const std::string& filePath)
	{
		auto fileStream = FileStream(
			filePath, std::ios::in | std::ios::ate | std::ios::binary);

		auto size = static_cast<size_t>(fileStream.tellg());
		fileStream.seekg(0, fileStream.beg);

		auto bytes = std::vector<char>(size);
		fileStream.read(bytes.data(), size);

		return bytes;
	}
	void FileStream::writeAllBytes(
		const std::string& filePath,
		const char* bytes,
		size_t count)
	{
		auto fileStream = FileStream(filePath, std::ios::out);
		fileStream.write(bytes, count);
	}
	void FileStream::writeAllBytes(
		const std::string& filePath,
		const std::vector<char>& bytes)
	{
		auto fileStream = FileStream(filePath, std::ios::out | std::ios::binary);
		fileStream.write(bytes.data(), bytes.size());
	}
}
