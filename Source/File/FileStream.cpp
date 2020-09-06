#include "Injector/File/FileStream.hpp"
#include "Injector/File/FileException.hpp"
#include "Injector/Memory/ByteSwap.hpp"

namespace Injector::File
{
	using namespace Injector::Memory;

	FileStream::FileStream() :
		fstream()
	{}
	FileStream::FileStream(const char* filePath, ios::openmode mode) :
		fstream(filePath, mode)
	{
		if(!is_open())
			throw FileException("Failed to open file", string(filePath));
	}
	FileStream::FileStream(const string& filePath, ios::openmode mode) :
		fstream(filePath, mode)
	{
		if(!is_open())
			throw FileException("Failed to open file", filePath);
	}
	FileStream::~FileStream()
	{}

	istream& FileStream::read(char& value)
	{
		return fstream::read(reinterpret_cast<char*>(&value), sizeof(char));
	}
	istream& FileStream::read(char* value, size_t count)
	{
		return fstream::read(reinterpret_cast<char*>(value), sizeof(char) * count);
	}
	istream& FileStream::read(uint8_t& value)
	{
		return fstream::read(reinterpret_cast<char*>(&value), sizeof(uint8_t));
	}
	istream& FileStream::read(uint8_t* value, size_t count)
	{
		return fstream::read(reinterpret_cast<char*>(value), sizeof(uint8_t) * count);
	}
	istream& FileStream::read(int8_t& value)
	{
		return fstream::read(reinterpret_cast<char*>(&value), sizeof(int8_t));
	}
	istream& FileStream::read(int8_t* value, size_t count)
	{
		return fstream::read(reinterpret_cast<char*>(value), sizeof(int8_t) * count);
	}
	istream& FileStream::read(uint16_t& value)
	{
		return fstream::read(reinterpret_cast<char*>(&value), sizeof(uint16_t));
	}
	istream& FileStream::read(uint16_t* value, size_t count)
	{
		return fstream::read(reinterpret_cast<char*>(value), sizeof(uint16_t) * count);
	}
	istream& FileStream::read(int16_t& value)
	{
		return fstream::read(reinterpret_cast<char*>(&value), sizeof(int16_t));
	}
	istream& FileStream::read(int16_t* value, size_t count)
	{
		return fstream::read(reinterpret_cast<char*>(value), sizeof(int16_t) * count);
	}
	istream& FileStream::read(uint32_t& value)
	{
		return fstream::read(reinterpret_cast<char*>(&value), sizeof(uint32_t));
	}
	istream& FileStream::read(uint32_t* value, size_t count)
	{
		return fstream::read(reinterpret_cast<char*>(value), sizeof(uint32_t) * count);
	}
	istream& FileStream::read(int32_t& value)
	{
		return fstream::read(reinterpret_cast<char*>(&value), sizeof(int32_t));
	}
	istream& FileStream::read(int32_t* value, size_t count)
	{
		return fstream::read(reinterpret_cast<char*>(value), sizeof(int32_t) * count);
	}
	istream& FileStream::read(uint64_t& value)
	{
		return fstream::read(reinterpret_cast<char*>(&value), sizeof(uint64_t));
	}
	istream& FileStream::read(uint64_t* value, size_t count)
	{
		return fstream::read(reinterpret_cast<char*>(value), sizeof(uint64_t) * count);
	}
	istream& FileStream::read(int64_t& value)
	{
		return fstream::read(reinterpret_cast<char*>(&value), sizeof(int64_t));
	}
	istream& FileStream::read(int64_t* value, size_t count)
	{
		return fstream::read(reinterpret_cast<char*>(value), sizeof(int64_t) * count);
	}
	istream& FileStream::read(float& value)
	{
		return fstream::read(reinterpret_cast<char*>(&value), sizeof(float));
	}
	istream& FileStream::read(float* value, size_t count)
	{
		return fstream::read(reinterpret_cast<char*>(value), sizeof(float) * count);
	}
	istream& FileStream::read(double& value)
	{
		return fstream::read(reinterpret_cast<char*>(&value), sizeof(double));
	}
	istream& FileStream::read(double* value, size_t count)
	{
		return fstream::read(reinterpret_cast<char*>(value), sizeof(double) * count);
	}

	istream& FileStream::readBE(uint16_t& value)
	{
		auto& stream = fstream::read(reinterpret_cast<char*>(&value), sizeof(uint16_t));
		value = ByteSwap::swapBigEndian(value);
		return stream;
	}
	istream& FileStream::readBE(int16_t& value)
	{
		auto& stream = fstream::read(reinterpret_cast<char*>(&value), sizeof(int16_t));
		value = ByteSwap::swapBigEndian(value);
		return stream;
	}
	istream& FileStream::readBE(uint32_t& value)
	{
		auto& stream = fstream::read(reinterpret_cast<char*>(&value), sizeof(uint32_t));
		value = ByteSwap::swapBigEndian(value);
		return stream;
	}
	istream& FileStream::readBE(int32_t& value)
	{
		auto& stream = fstream::read(reinterpret_cast<char*>(&value), sizeof(int32_t));
		value = ByteSwap::swapBigEndian(value);
		return stream;
	}
	istream& FileStream::readBE(uint64_t& value)
	{
		auto& stream = fstream::read(reinterpret_cast<char*>(&value), sizeof(uint64_t));
		value = ByteSwap::swapBigEndian(value);
		return stream;
	}
	istream& FileStream::readBE(int64_t& value)
	{
		auto& stream = fstream::read(reinterpret_cast<char*>(&value), sizeof(int64_t));
		value = ByteSwap::swapBigEndian(value);
		return stream;
	}
	istream& FileStream::readBE(float& value)
	{
		auto& stream = fstream::read(reinterpret_cast<char*>(&value), sizeof(float));
		value = ByteSwap::swapBigEndian(value);
		return stream;
	}
	istream& FileStream::readBE(double& value)
	{
		auto& stream = fstream::read(reinterpret_cast<char*>(&value), sizeof(double));
		value = ByteSwap::swapBigEndian(value);
		return stream;
	}

	istream& FileStream::readLE(uint16_t& value)
	{
		auto& stream = fstream::read(reinterpret_cast<char*>(&value), sizeof(uint16_t));
		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}
	istream& FileStream::readLE(int16_t& value)
	{
		auto& stream = fstream::read(reinterpret_cast<char*>(&value), sizeof(int16_t));
		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}
	istream& FileStream::readLE(uint32_t& value)
	{
		auto& stream = fstream::read(reinterpret_cast<char*>(&value), sizeof(uint32_t));
		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}
	istream& FileStream::readLE(int32_t& value)
	{
		auto& stream = fstream::read(reinterpret_cast<char*>(&value), sizeof(int32_t));
		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}
	istream& FileStream::readLE(uint64_t& value)
	{
		auto& stream = fstream::read(reinterpret_cast<char*>(&value), sizeof(uint64_t));
		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}
	istream& FileStream::readLE(int64_t& value)
	{
		auto& stream = fstream::read(reinterpret_cast<char*>(&value), sizeof(int64_t));
		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}
	istream& FileStream::readLE(float& value)
	{
		auto& stream = fstream::read(reinterpret_cast<char*>(&value), sizeof(float));
		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}
	istream& FileStream::readLE(double& value)
	{
		auto& stream = fstream::read(reinterpret_cast<char*>(&value), sizeof(double));
		value = ByteSwap::swapLittleEndian(value);
		return stream;
	}

	ostream& FileStream::write(char value)
	{
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(char));
	}
	ostream& FileStream::write(const char* value, size_t count)
	{
		return fstream::write(reinterpret_cast<const char*>(value), sizeof(char) * count);
	}
	ostream& FileStream::write(uint8_t value)
	{
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(uint8_t));
	}
	ostream& FileStream::write(const uint8_t* value, size_t count)
	{
		return fstream::write(reinterpret_cast<const char*>(value), sizeof(uint8_t) * count);
	}
	ostream& FileStream::write(int8_t value)
	{
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(int8_t));
	}
	ostream& FileStream::write(const int8_t* value, size_t count)
	{
		return fstream::write(reinterpret_cast<const char*>(value), sizeof(int8_t) * count);
	}
	ostream& FileStream::write(uint16_t value)
	{
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(uint16_t));
	}
	ostream& FileStream::write(const uint16_t* value, size_t count)
	{
		return fstream::write(reinterpret_cast<const char*>(value), sizeof(uint16_t) * count);
	}
	ostream& FileStream::write(int16_t value)
	{
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(int16_t));
	}
	ostream& FileStream::write(const int16_t* value, size_t count)
	{
		return fstream::write(reinterpret_cast<const char*>(value), sizeof(int16_t) * count);
	}
	ostream& FileStream::write(uint32_t value)
	{
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(uint32_t));
	}
	ostream& FileStream::write(const uint32_t* value, size_t count)
	{
		return fstream::write(reinterpret_cast<const char*>(value), sizeof(uint32_t) * count);
	}
	ostream& FileStream::write(int32_t value)
	{
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(int32_t));
	}
	ostream& FileStream::write(const int32_t* value, size_t count)
	{
		return fstream::write(reinterpret_cast<const char*>(value), sizeof(int32_t) * count);
	}
	ostream& FileStream::write(uint64_t value)
	{
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(uint64_t));
	}
	ostream& FileStream::write(const uint64_t* value, size_t count)
	{
		return fstream::write(reinterpret_cast<const char*>(value), sizeof(uint64_t) * count);
	}
	ostream& FileStream::write(int64_t value)
	{
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(int64_t));
	}
	ostream& FileStream::write(const int64_t* value, size_t count)
	{
		return fstream::write(reinterpret_cast<const char*>(value), sizeof(int64_t) * count);
	}
	ostream& FileStream::write(float value)
	{
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(float));
	}
	ostream& FileStream::write(const float* value, size_t count)
	{
		return fstream::write(reinterpret_cast<const char*>(value), sizeof(float) * count);
	}
	ostream& FileStream::write(double value)
	{
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(double));
	}
	ostream& FileStream::write(const double* value, size_t count)
	{
		return fstream::write(reinterpret_cast<const char*>(value), sizeof(double) * count);
	}

	ostream& FileStream::writeBE(uint16_t value)
	{
		value = ByteSwap::swapBigEndian(value);
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(uint16_t));
	}
	ostream& FileStream::writeBE(int16_t value)
	{
		value = ByteSwap::swapBigEndian(value);
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(int16_t));
	}
	ostream& FileStream::writeBE(uint32_t value)
	{
		value = ByteSwap::swapBigEndian(value);
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(uint32_t));
	}
	ostream& FileStream::writeBE(int32_t value)
	{
		value = ByteSwap::swapBigEndian(value);
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(int32_t));
	}
	ostream& FileStream::writeBE(uint64_t value)
	{
		value = ByteSwap::swapBigEndian(value);
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(uint64_t));
	}
	ostream& FileStream::writeBE(int64_t value)
	{
		value = ByteSwap::swapBigEndian(value);
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(int64_t));
	}
	ostream& FileStream::writeBE(float value)
	{
		value = ByteSwap::swapBigEndian(value);
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(float));
	}
	ostream& FileStream::writeBE(double value)
	{
		value = ByteSwap::swapBigEndian(value);
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(double));
	}

	ostream& FileStream::writeLE(uint16_t value)
	{
		value = ByteSwap::swapLittleEndian(value);
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(uint16_t));
	}
	ostream& FileStream::writeLE(int16_t value)
	{
		value = ByteSwap::swapLittleEndian(value);
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(int16_t));
	}
	ostream& FileStream::writeLE(uint32_t value)
	{
		value = ByteSwap::swapLittleEndian(value);
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(uint32_t));
	}
	ostream& FileStream::writeLE(int32_t value)
	{
		value = ByteSwap::swapLittleEndian(value);
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(int32_t));
	}
	ostream& FileStream::writeLE(uint64_t value)
	{
		value = ByteSwap::swapLittleEndian(value);
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(uint64_t));
	}
	ostream& FileStream::writeLE(int64_t value)
	{
		value = ByteSwap::swapLittleEndian(value);
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(int64_t));
	}
	ostream& FileStream::writeLE(float value)
	{
		value = ByteSwap::swapLittleEndian(value);
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(float));
	}
	ostream& FileStream::writeLE(double value)
	{
		value = ByteSwap::swapLittleEndian(value);
		return fstream::write(reinterpret_cast<const char*>(&value), sizeof(double));
	}

	string FileStream::readAllText(
		const string& filePath)
	{
		auto fileStream = FileStream(filePath, ios::in | ios::ate);

		auto size = static_cast<size_t>(fileStream.tellg());
		fileStream.seekg(0, fileStream.beg);

		auto text = string(size, ' ');
		fileStream.read(text.data(), size);

		return text;
	}
	void FileStream::writeAllText(
		const string& filePath,
		const char* text,
		size_t count)
	{
		auto fileStream = FileStream(filePath, ios::out);
		fileStream.write(text, count);
	}
	void FileStream::writeAllText(
		const string& filePath,
		const string& text)
	{
		auto fileStream = FileStream(filePath, ios::out);
		fileStream.write(text.data(), text.size());
	}
	
	vector<char> FileStream::readAllBytes(
		const string& filePath)
	{
		auto fileStream = FileStream(
			filePath, ios::in | ios::ate | ios::binary);

		auto size = static_cast<size_t>(fileStream.tellg());
		fileStream.seekg(0, fileStream.beg);

		auto bytes = vector<char>(size);
		fileStream.read(bytes.data(), size);

		return bytes;
	}
	void FileStream::writeAllBytes(
		const string& filePath,
		const char* bytes,
		size_t count)
	{
		auto fileStream = FileStream(filePath, ios::out);
		fileStream.write(bytes, count);
	}
	void FileStream::writeAllBytes(
		const string& filePath,
		const vector<char>& bytes)
	{
		auto fileStream = FileStream(filePath, ios::out | ios::binary);
		fileStream.write(bytes.data(), bytes.size());
	}
}
