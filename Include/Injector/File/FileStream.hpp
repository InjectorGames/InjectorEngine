#pragma once
#include <vector>
#include <fstream>
#include <filesystem>

namespace Injector::File
{
	using namespace std;

	class FileStream : public fstream
	{
	public:
		FileStream();
		FileStream(const char* filePath,
			ios::openmode mode = ios::in | ios::out);
		FileStream(const std::string& filePath,
			ios::openmode mode = ios::in | ios::out);
		virtual ~FileStream();

		istream& read(char& value);
		istream& read(char* value, size_t count);
		istream& read(uint8_t& value);
		istream& read(uint8_t* value, size_t count);
		istream& read(int8_t& value);
		istream& read(int8_t* value, size_t count);
		istream& read(uint16_t& value);
		istream& read(uint16_t* value, size_t count);
		istream& read(int16_t& value);
		istream& read(int16_t* value, size_t count);
		istream& read(uint32_t& value);
		istream& read(uint32_t* value, size_t count);
		istream& read(int32_t& value);
		istream& read(int32_t* value, size_t count);
		istream& read(uint64_t& value);
		istream& read(uint64_t* value, size_t count);
		istream& read(int64_t& value);
		istream& read(int64_t* value, size_t count);
		istream& read(float& value);
		istream& read(float* value, size_t count);
		istream& read(double& value);
		istream& read(double* value, size_t count);

		istream& readBE(uint16_t& value);
		istream& readBE(int16_t& value);
		istream& readBE(uint32_t& value);
		istream& readBE(int32_t& value);
		istream& readBE(uint64_t& value);
		istream& readBE(int64_t& value);
		istream& readBE(float& value);
		istream& readBE(double& value);

		istream& readLE(uint16_t& value);
		istream& readLE(int16_t& value);
		istream& readLE(uint32_t& value);
		istream& readLE(int32_t& value);
		istream& readLE(uint64_t& value);
		istream& readLE(int64_t& value);
		istream& readLE(float& value);
		istream& readLE(double& value);

		ostream& write(char value);
		ostream& write(const char* value, size_t count);
		ostream& write(uint8_t value);
		ostream& write(const uint8_t* value, size_t count);
		ostream& write(int8_t value);
		ostream& write(const int8_t* value, size_t count);
		ostream& write(uint16_t value);
		ostream& write(const uint16_t* value, size_t count);
		ostream& write(int16_t value);
		ostream& write(const int16_t* value, size_t count);
		ostream& write(uint32_t value);
		ostream& write(const uint32_t* value, size_t count);
		ostream& write(int32_t value);
		ostream& write(const int32_t* value, size_t count);
		ostream& write(uint64_t value);
		ostream& write(const uint64_t* value, size_t count);
		ostream& write(int64_t value);
		ostream& write(const int64_t* value, size_t count);
		ostream& write(float value);
		ostream& write(const float* value, size_t count);
		ostream& write(double value);
		ostream& write(const double* value, size_t count);

		ostream& writeBE(uint16_t value);
		ostream& writeBE(int16_t value);
		ostream& writeBE(uint32_t value);
		ostream& writeBE(int32_t value);
		ostream& writeBE(uint64_t value);
		ostream& writeBE(int64_t value);
		ostream& writeBE(float value);
		ostream& writeBE(double value);

		ostream& writeLE(uint16_t value);
		ostream& writeLE(int16_t value);
		ostream& writeLE(uint32_t value);
		ostream& writeLE(int32_t value);
		ostream& writeLE(uint64_t value);
		ostream& writeLE(int64_t value);
		ostream& writeLE(float value);
		ostream& writeLE(double value);

		static string readAllText(
			const string& filePath);
		static void writeAllText(
			const string& filePath,
			const char* text,
			size_t count);
		static void writeAllText(
			const string& filePath,
			const string& text);

		static vector<char> readAllBytes(
			const string& filePath);
		static void writeAllBytes(
			const string& filePath,
			const char* bytes,
			size_t count);
		static void writeAllBytes(
			const string& filePath,
			const vector<char>& bytes);
	};
}
