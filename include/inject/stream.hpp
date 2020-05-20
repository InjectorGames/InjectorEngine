#pragma once
#include <SDL_rwops.h>
#include <SDL_endian.h>

#include <string>
#include <stdexcept>

namespace inject
{
	class Stream
	{
	protected:
		SDL_RWops* context;
	public:
		Stream(SDL_RWops* const _context) :
			context(_context)
		{}
		virtual ~Stream()
		{}

		inline const int64_t getSize()
		{
			auto size = static_cast<int64_t>(context->size(context));
			if(size < 0)
				throw std::runtime_error("Failed to get size. Error: " +
					std::string(SDL_GetError()));
			return size;
		}

		// TODO: *reinterpret_cast<Uint32*>(&value)

		inline void read(void* const buffer, const size_t size, const size_t count)
		{
			if (context->read(context, buffer, size, count) != count)
				throw std::runtime_error("Failed to read. Error: " +
					std::string(SDL_GetError()));
		}
		inline void read(char* const buffer, const size_t count)
		{
			if (context->read(context, buffer, sizeof(char), count) != count)
				throw std::runtime_error("Failed to read. Error: " +
					std::string(SDL_GetError()));
		}
		inline void read(uint8_t* const buffer, const size_t count)
		{
			if (context->read(context, buffer, sizeof(uint8_t), count) != count)
				throw std::runtime_error("Failed to read. Error: " +
					std::string(SDL_GetError()));
		}
		inline void read(int8_t* const buffer, const size_t count)
		{
			if (context->read(context, buffer, sizeof(int8_t), count) != count)
				throw std::runtime_error("Failed to read. Error: " +
					std::string(SDL_GetError()));
		}
		inline void read(uint8_t* const value)
		{
			if (context->read(context, value, sizeof(uint8_t), 1) != 1)
				throw std::runtime_error("Failed to write. Error: " +
					std::string(SDL_GetError()));
		}
		inline void read(int8_t* const value)
		{
			if (context->read(context, value, sizeof(int8_t), 1) != 1)
				throw std::runtime_error("Failed to write. Error: " +
					std::string(SDL_GetError()));
		}
		inline void read(uint16_t* const value)
		{
			auto _value = static_cast<uint16_t>(0);
			if (context->read(context, &_value, sizeof(uint16_t), 1) != 1)
				throw std::runtime_error("Failed to write. Error: " +
					std::string(SDL_GetError()));
			*value = SDL_SwapBE16(_value);
		}
		inline void read(uint32_t* const value)
		{
			auto _value = static_cast<uint32_t>(0);
			if (context->read(context, &_value, sizeof(uint32_t), 1) != 1)
				throw std::runtime_error("Failed to write. Error: " +
					std::string(SDL_GetError()));
			*value = SDL_SwapBE32(_value);
		}
		inline void read(uint64_t* const value)
		{
			auto _value = static_cast<uint64_t>(0);
			if (context->read(context, &_value, sizeof(uint64_t), 1) != 1)
				throw std::runtime_error("Failed to write. Error: " +
					std::string(SDL_GetError()));
			*value = SDL_SwapBE64(_value);
		}
		inline void read(float* const value)
		{
			auto _value = static_cast<float>(0);
			if (context->read(context, &_value, sizeof(float), 1) != 1)
				throw std::runtime_error("Failed to write. Error: " +
					std::string(SDL_GetError()));
			*value = SDL_SwapFloatBE(_value);
		}

		inline void write(const void* const buffer, const size_t size, const size_t count)
		{
			if (context->write(context, buffer, size, count) != count)
				throw std::runtime_error("Failed to write. Error: " +
					std::string(SDL_GetError()));
		}
		inline void write(const char* const buffer, const size_t count)
		{
			if (context->write(context, buffer, sizeof(char), count) != count)
				throw std::runtime_error("Failed to write. Error: " +
					std::string(SDL_GetError()));
		}
		inline void write(const uint8_t* const buffer, const size_t count)
		{
			if (context->write(context, buffer, sizeof(uint8_t), count) != count)
				throw std::runtime_error("Failed to write. Error: " +
					std::string(SDL_GetError()));
		}
		inline void write(const int8_t* const buffer, const size_t count)
		{
			if (context->write(context, buffer, sizeof(int8_t), count) != count)
				throw std::runtime_error("Failed to write. Error: " +
					std::string(SDL_GetError()));
		}
		inline void write(const uint8_t value)
		{
			if (context->write(context, &value, sizeof(uint8_t), 1) != 1)
				throw std::runtime_error("Failed to write. Error: " +
					std::string(SDL_GetError()));
		}
		inline void write(const int8_t value)
		{
			if (context->write(context, &value, sizeof(int8_t), 1) != 1)
				throw std::runtime_error("Failed to write. Error: " +
					std::string(SDL_GetError()));
		}
		inline void write(const uint16_t value)
		{
			auto _value = SDL_SwapBE16(value);
			if (context->write(context, &_value, sizeof(uint16_t), 1) != 1)
				throw std::runtime_error("Failed to write. Error: " +
					std::string(SDL_GetError()));
		}
		inline void write(const uint32_t const value)
		{
			auto _value = SDL_SwapBE32(value);
			if (context->write(context, &_value, sizeof(uint32_t), 1) != 1)
				throw std::runtime_error("Failed to write. Error: " +
					std::string(SDL_GetError()));
		}
		inline void write(const uint64_t const value)
		{
			auto _value = SDL_SwapBE64(value);
			if (context->write(context, &_value, sizeof(uint64_t), 1) != 1)
				throw std::runtime_error("Failed to write. Error: " +
					std::string(SDL_GetError()));

		}
		inline void write(const float const value)
		{
			auto _value = SDL_SwapFloatBE(value);
			if (context->write(context, &_value, sizeof(float), 1) != 1)
				throw std::runtime_error("Failed to write. Error: " +
					std::string(SDL_GetError()));
		}
	};
}
