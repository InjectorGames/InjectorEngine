#pragma once
#include <injector/defines.hpp>

#include <vector>
#include <fstream>
#include <filesystem>

namespace INJECTOR_NAMESPACE
{

	
	class FileStream : public std::fstream
	{
	public:
		FileStream();
		FileStream(const char* filePath,
			std::ios::openmode mode = std::ios::in | std::ios::out);
		FileStream(const std::string& filePath,
			std::ios::openmode mode = std::ios::in | std::ios::out);
		virtual ~FileStream();

		std::istream& read(char& value);
		std::istream& read(char* value, size_t count);
		std::istream& read(uint8_t& value);
		std::istream& read(uint8_t* value, size_t count);
		std::istream& read(int8_t& value);
		std::istream& read(int8_t* value, size_t count);
		std::istream& read(uint16_t& value);
		std::istream& read(uint16_t* value, size_t count);
		std::istream& read(int16_t& value);
		std::istream& read(int16_t* value, size_t count);
		std::istream& read(uint32_t& value);
		std::istream& read(uint32_t* value, size_t count);
		std::istream& read(int32_t& value);
		std::istream& read(int32_t* value, size_t count);
		std::istream& read(uint64_t& value);
		std::istream& read(uint64_t* value, size_t count);
		std::istream& read(int64_t& value);
		std::istream& read(int64_t* value, size_t count);
		std::istream& read(float& value);
		std::istream& read(float* value, size_t count);
		std::istream& read(double& value);
		std::istream& read(double* value, size_t count);

		std::istream& readBE(uint16_t& value);
		std::istream& readBE(int16_t& value);
		std::istream& readBE(uint32_t& value);
		std::istream& readBE(int32_t& value);
		std::istream& readBE(uint64_t& value);
		std::istream& readBE(int64_t& value);
		std::istream& readBE(float& value);
		std::istream& readBE(double& value);

		std::istream& readLE(uint16_t& value);
		std::istream& readLE(int16_t& value);
		std::istream& readLE(uint32_t& value);
		std::istream& readLE(int32_t& value);
		std::istream& readLE(uint64_t& value);
		std::istream& readLE(int64_t& value);
		std::istream& readLE(float& value);
		std::istream& readLE(double& value);

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

		std::ostream& writeBE(uint16_t value);
		std::ostream& writeBE(int16_t value);
		std::ostream& writeBE(uint32_t value);
		std::ostream& writeBE(int32_t value);
		std::ostream& writeBE(uint64_t value);
		std::ostream& writeBE(int64_t value);
		std::ostream& writeBE(float value);
		std::ostream& writeBE(double value);

		std::ostream& writeLE(uint16_t value);
		std::ostream& writeLE(int16_t value);
		std::ostream& writeLE(uint32_t value);
		std::ostream& writeLE(int32_t value);
		std::ostream& writeLE(uint64_t value);
		std::ostream& writeLE(int64_t value);
		std::ostream& writeLE(float value);
		std::ostream& writeLE(double value);

		static std::string readAllText(
			const std::string& filePath);
		static void writeAllText(
			const std::string& filePath,
			const char* text,
			size_t count);
		static void writeAllText(
			const std::string& filePath,
			const std::string& text);

		static std::vector<char> readAllBytes(
			const std::string& filePath);
		static void writeAllBytes(
			const std::string& filePath,
			const char* bytes,
			size_t count);
		static void writeAllBytes(
			const std::string& filePath,
			const std::vector<char>& bytes);
	};
}
