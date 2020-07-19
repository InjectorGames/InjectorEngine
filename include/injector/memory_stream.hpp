#pragma once
#include <inject/defines.hpp>
#include <SDL_endian.h>

#include <sstream>

namespace INJECT_NAMESPACE
{
	class MemoryStream : public std::stringstream
	{
	public:
		MemoryStream(
			const std::ios::openmode mode =
			ios_base::in | ios_base::out) :
			std::stringstream(mode)
		{}
		MemoryStream(
			const std::string& string,
			const std::ios::openmode mode =
			ios_base::in | ios_base::out) :
			std::stringstream(string, mode)
		{}
		virtual ~MemoryStream()
		{}

		inline std::istream& read(void* value, const size_t count)
		{
			return std::stringstream::read(reinterpret_cast<char*>(value), count);
		}
		inline std::istream& read(uint8_t* value)
		{
			return std::stringstream::read(reinterpret_cast<char*>(value), sizeof(uint8_t));
		}
		inline std::istream& read(uint8_t* value, const size_t count)
		{
			return std::stringstream::read(reinterpret_cast<char*>(value), sizeof(uint8_t) * count);
		}
		inline std::istream& read(int8_t* value)
		{
			return std::stringstream::read(reinterpret_cast<char*>(value), sizeof(int8_t));
		}
		inline std::istream& read(int8_t* value, const size_t count)
		{
			return std::stringstream::read(reinterpret_cast<char*>(value), sizeof(int8_t) * count);
		}
		inline std::istream& read(uint16_t* value)
		{
			return std::stringstream::read(reinterpret_cast<char*>(value), sizeof(uint16_t));
		}
		inline std::istream& read(uint16_t* value, const size_t count)
		{
			return std::stringstream::read(reinterpret_cast<char*>(value), sizeof(uint16_t) * count);
		}
		inline std::istream& read(int16_t* value)
		{
			return std::stringstream::read(reinterpret_cast<char*>(value), sizeof(int16_t));
		}
		inline std::istream& read(int16_t* value, const size_t count)
		{
			return std::stringstream::read(reinterpret_cast<char*>(value), sizeof(int16_t) * count);
		}
		inline std::istream& read(uint32_t* value)
		{
			return std::stringstream::read(reinterpret_cast<char*>(value), sizeof(uint32_t));
		}
		inline std::istream& read(uint32_t* value, const size_t count)
		{
			return std::stringstream::read(reinterpret_cast<char*>(value), sizeof(uint32_t) * count);
		}
		inline std::istream& read(int32_t* value)
		{
			return std::stringstream::read(reinterpret_cast<char*>(value), sizeof(int32_t));
		}
		inline std::istream& read(int32_t* value, const size_t count)
		{
			return std::stringstream::read(reinterpret_cast<char*>(value), sizeof(int32_t) * count);
		}
		inline std::istream& read(uint64_t* value)
		{
			return std::stringstream::read(reinterpret_cast<char*>(value), sizeof(uint64_t));
		}
		inline std::istream& read(uint64_t* value, const size_t count)
		{
			return std::stringstream::read(reinterpret_cast<char*>(value), sizeof(uint64_t) * count);
		}
		inline std::istream& read(int64_t* value)
		{
			return std::stringstream::read(reinterpret_cast<char*>(value), sizeof(int64_t));
		}
		inline std::istream& read(int64_t* value, const size_t count)
		{
			return std::stringstream::read(reinterpret_cast<char*>(value), sizeof(int64_t) * count);
		}
		inline std::istream& read(float* value)
		{
			return std::stringstream::read(reinterpret_cast<char*>(value), sizeof(float));
		}
		inline std::istream& read(float* value, const size_t count)
		{
			return std::stringstream::read(reinterpret_cast<char*>(value), sizeof(float) * count);
		}
		inline std::istream& read(double* value)
		{
			return std::stringstream::read(reinterpret_cast<char*>(value), sizeof(double));
		}
		inline std::istream& read(double* value, const size_t count)
		{
			return std::stringstream::read(reinterpret_cast<char*>(value), sizeof(double) * count);
		}

		inline std::istream& readBE(uint16_t* value)
		{
			auto& stream = std::stringstream::read(reinterpret_cast<char*>(value), sizeof(uint16_t));
			*value = static_cast<uint16_t>(SDL_SwapBE16(*value));
			return stream;
		}
		inline std::istream& readBE(int16_t* value)
		{
			return readBE(reinterpret_cast<uint16_t*>(value));
		}
		inline std::istream& readBE(uint32_t* value)
		{
			auto& stream = std::stringstream::read(reinterpret_cast<char*>(value), sizeof(uint32_t));
			*value = static_cast<uint32_t>(SDL_SwapBE32(*value));
			return stream;
		}
		inline std::istream& readBE(int32_t* value)
		{
			return readBE(reinterpret_cast<uint32_t*>(value));
		}
		inline std::istream& readBE(uint64_t* value)
		{
			auto& stream = std::stringstream::read(reinterpret_cast<char*>(value), sizeof(uint64_t));
			*value = static_cast<uint64_t>(SDL_SwapBE64(*value));
			return stream;
		}
		inline std::istream& readBE(int64_t* value)
		{
			return readBE(reinterpret_cast<uint64_t*>(value));
		}
		inline std::istream& readBE(float* value)
		{
			auto& stream = std::stringstream::read(reinterpret_cast<char*>(value), sizeof(float));
			*value = static_cast<float>(SDL_SwapFloatBE(*value));
			return stream;
		}

		inline std::istream& readLE(uint16_t* value)
		{
			auto& stream = std::stringstream::read(reinterpret_cast<char*>(value), sizeof(uint16_t));
			*value = static_cast<uint16_t>(SDL_SwapLE16(*value));
			return stream;
		}
		inline std::istream& readLE(int16_t* value)
		{
			return readLE(reinterpret_cast<uint16_t*>(value));
		}
		inline std::istream& readLE(uint32_t* value)
		{
			auto& stream = std::stringstream::read(reinterpret_cast<char*>(value), sizeof(uint32_t));
			*value = static_cast<uint32_t>(SDL_SwapLE32(*value));
			return stream;
		}
		inline std::istream& readLE(int32_t* value)
		{
			return readLE(reinterpret_cast<uint32_t*>(value));
		}
		inline std::istream& readLE(uint64_t* value)
		{
			auto& stream = std::stringstream::read(reinterpret_cast<char*>(value), sizeof(uint64_t));
			*value = static_cast<uint64_t>(SDL_SwapLE64(*value));
			return stream;
		}
		inline std::istream& readLE(int64_t* value)
		{
			return readLE(reinterpret_cast<uint64_t*>(value));
		}
		inline std::istream& readLE(float* value)
		{
			auto& stream = std::stringstream::read(reinterpret_cast<char*>(value), sizeof(float));
			*value = static_cast<float>(SDL_SwapFloatLE(*value));
			return stream;
		}

		inline std::ostream& write(const void* value, const size_t count)
		{
			return std::stringstream::write(reinterpret_cast<const char*>(value), count);
		}
		inline std::ostream& write(const uint8_t* value)
		{
			return std::stringstream::write(reinterpret_cast<const char*>(value), sizeof(uint8_t));
		}
		inline std::ostream& write(const uint8_t* value, const size_t count)
		{
			return std::stringstream::write(reinterpret_cast<const char*>(value), sizeof(uint8_t) * count);
		}
		inline std::ostream& write(const int8_t* value)
		{
			return std::stringstream::write(reinterpret_cast<const char*>(value), sizeof(int8_t));
		}
		inline std::ostream& write(const int8_t* value, const size_t count)
		{
			return std::stringstream::write(reinterpret_cast<const char*>(value), sizeof(int8_t) * count);
		}
		inline std::ostream& write(const uint16_t* value)
		{
			return std::stringstream::write(reinterpret_cast<const char*>(value), sizeof(uint16_t));
		}
		inline std::ostream& write(const uint16_t* value, const size_t count)
		{
			return std::stringstream::write(reinterpret_cast<const char*>(value), sizeof(uint16_t) * count);
		}
		inline std::ostream& write(const int16_t* value)
		{
			return std::stringstream::write(reinterpret_cast<const char*>(value), sizeof(int16_t));
		}
		inline std::ostream& write(const int16_t* value, const size_t count)
		{
			return std::stringstream::write(reinterpret_cast<const char*>(value), sizeof(int16_t) * count);
		}
		inline std::ostream& write(const uint32_t* value)
		{
			return std::stringstream::write(reinterpret_cast<const char*>(value), sizeof(uint32_t));
		}
		inline std::ostream& write(const uint32_t* value, const size_t count)
		{
			return std::stringstream::write(reinterpret_cast<const char*>(value), sizeof(uint32_t) * count);
		}
		inline std::ostream& write(const int32_t* value)
		{
			return std::stringstream::write(reinterpret_cast<const char*>(value), sizeof(int32_t));
		}
		inline std::ostream& write(const int32_t* value, const size_t count)
		{
			return std::stringstream::write(reinterpret_cast<const char*>(value), sizeof(int32_t) * count);
		}
		inline std::ostream& write(const uint64_t* value)
		{
			return std::stringstream::write(reinterpret_cast<const char*>(value), sizeof(uint64_t));
		}
		inline std::ostream& write(const uint64_t* value, const size_t count)
		{
			return std::stringstream::write(reinterpret_cast<const char*>(value), sizeof(uint64_t) * count);
		}
		inline std::ostream& write(const int64_t* value)
		{
			return std::stringstream::write(reinterpret_cast<const char*>(value), sizeof(int64_t));
		}
		inline std::ostream& write(const int64_t* value, const size_t count)
		{
			return std::stringstream::write(reinterpret_cast<const char*>(value), sizeof(int64_t) * count);
		}
		inline std::ostream& write(const float* value)
		{
			return std::stringstream::write(reinterpret_cast<const char*>(value), sizeof(float));
		}
		inline std::ostream& write(const float* value, const size_t count)
		{
			return std::stringstream::write(reinterpret_cast<const char*>(value), sizeof(float) * count);
		}
		inline std::ostream& write(const double* value)
		{
			return std::stringstream::write(reinterpret_cast<const char*>(value), sizeof(double));
		}
		inline std::ostream& write(const double* value, const size_t count)
		{
			return std::stringstream::write(reinterpret_cast<const char*>(value), sizeof(double) * count);
		}

		inline std::ostream& writeBE(const uint16_t* value)
		{
			const auto _value = static_cast<uint16_t>(SDL_SwapBE16(*value));
			return std::stringstream::write(reinterpret_cast<const char*>(&_value), sizeof(uint16_t));
		}
		inline std::ostream& writeBE(const int16_t* value)
		{
			return writeBE(reinterpret_cast<const uint32_t*>(value));
		}
		inline std::ostream& writeBE(const uint32_t* value)
		{
			const auto _value = static_cast<uint32_t>(SDL_SwapBE32(*value));
			return std::stringstream::write(reinterpret_cast<const char*>(&_value), sizeof(uint32_t));
		}
		inline std::ostream& writeBE(const int32_t* value)
		{
			return writeBE(reinterpret_cast<const uint32_t*>(value));
		}
		inline std::ostream& writeBE(const uint64_t* value)
		{
			const auto _value = static_cast<uint64_t>(SDL_SwapBE64(*value));
			return std::stringstream::write(reinterpret_cast<const char*>(&_value), sizeof(uint64_t));
		}
		inline std::ostream& writeBE(const int64_t* value)
		{
			return writeBE(reinterpret_cast<const uint64_t*>(value));
		}
		inline std::ostream& writeBE(const float* value)
		{
			const auto _value = static_cast<float>(SDL_SwapFloatBE(*value));
			return std::stringstream::write(reinterpret_cast<const char*>(&_value), sizeof(float));
		}

		inline std::ostream& writeLE(const uint16_t* value)
		{
			const auto _value = static_cast<uint16_t>(SDL_SwapLE16(*value));
			return std::stringstream::write(reinterpret_cast<const char*>(&_value), sizeof(uint16_t));
		}
		inline std::ostream& writeLE(const int16_t* value)
		{
			return writeLE(reinterpret_cast<const uint32_t*>(value));
		}
		inline std::ostream& writeLE(const uint32_t* value)
		{
			const auto _value = static_cast<uint32_t>(SDL_SwapLE32(*value));
			return std::stringstream::write(reinterpret_cast<const char*>(&_value), sizeof(uint32_t));
		}
		inline std::ostream& writeLE(const int32_t* value)
		{
			return writeLE(reinterpret_cast<const uint32_t*>(value));
		}
		inline std::ostream& writeLE(const uint64_t* value)
		{
			const auto _value = static_cast<uint64_t>(SDL_SwapLE64(*value));
			return std::stringstream::write(reinterpret_cast<const char*>(&_value), sizeof(uint64_t));
		}
		inline std::ostream& writeLE(const int64_t* value)
		{
			return writeLE(reinterpret_cast<const uint64_t*>(value));
		}
		inline std::ostream& writeLE(const float* value)
		{
			const auto _value = static_cast<float>(SDL_SwapFloatLE(*value));
			return std::stringstream::write(reinterpret_cast<const char*>(&_value), sizeof(float));
		}
	};
}