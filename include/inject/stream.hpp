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
		enum class Whence : int
		{
			Begin = RW_SEEK_SET,
			Current = RW_SEEK_CUR,
			End = RW_SEEK_END,
		};

		Stream(SDL_RWops* const _context) :
			context(_context)
		{}
		virtual ~Stream()
		{}

		inline const int64_t getSize()
		{
			return static_cast<int64_t>(context->size(context));
		}
		inline const int64_t seek(int64_t offset, Whence whence = Whence::Current)
		{
			return static_cast<int64_t>(context->seek(context, static_cast<Sint64>(offset), static_cast<int>(whence)));
		}

		inline const size_t read(void* values, const size_t size, const size_t count)
		{
			return context->read(context, values, size, count);
		}
		inline const size_t read(void* values, const size_t count)
		{
			return context->read(context, values, 1, count);
		}
		inline const size_t read(char* values, const size_t count)
		{
			return context->read(context, values, sizeof(char), count) * sizeof(char);
		}
		inline const size_t read(uint8_t* values, const size_t count)
		{
			return context->read(context, values, sizeof(uint8_t), count) * sizeof(uint8_t);
		}
		inline const size_t read(int8_t* values, const size_t count)
		{
			return context->read(context, values, sizeof(int8_t), count) * sizeof(int8_t);
		}
		inline const size_t read(uint16_t* values, const size_t count)
		{
			auto size = static_cast<size_t>(0);
			auto number = static_cast<Uint16>(0);
			for (size_t i = 0; i < count; i++)
			{
				size += context->read(context, &number, sizeof(Uint16), 1);
				values[i] = static_cast<int16_t>(SDL_SwapBE16(number));
			}
			return size * sizeof(Uint16);
		}
		inline const size_t read(uint32_t* values, const size_t count)
		{
			auto size = static_cast<size_t>(0);
			auto number = static_cast<Uint32>(0);
			for (size_t i = 0; i < count; i++)
			{
				size += context->read(context, &number, sizeof(Uint32), 1);
				values[i] = static_cast<int32_t>(SDL_SwapBE32(number));
			}
			return size * sizeof(Uint32);
		}
		inline const size_t read(uint64_t* values, const size_t count)
		{
			auto size = static_cast<size_t>(0);
			auto number = static_cast<Uint64>(0);
			for (size_t i = 0; i < count; i++)
			{
				size += context->read(context, &number, sizeof(Uint64), 1);
				values[i] = static_cast<int32_t>(SDL_SwapBE64(number));
			}
			return size * sizeof(Uint64);
		}
		inline const size_t read(uint8_t* value)
		{
			return context->read(context, value, sizeof(uint8_t), 1) * sizeof(uint8_t);
		}
		inline const size_t read(int8_t* value)
		{
			return context->read(context, value, sizeof(int8_t), 1) * sizeof(int8_t);
		}
		inline const size_t read(uint16_t* value)
		{
			auto number = static_cast<Uint16>(0);
			auto size = context->read(context, &number, sizeof(Uint16), 1);
			*value = static_cast<int16_t>(SDL_SwapBE16(number));
			return size * sizeof(Uint16);
		}
		inline const size_t read(int16_t* value)
		{
			auto number = static_cast<Uint16>(0);
			auto size = context->read(context, &number, sizeof(Uint16), 1);
			number = SDL_SwapBE16(number);
			*value = *reinterpret_cast<int16_t*>(&number);
			return size * sizeof(Uint16);
		}
		inline const size_t read(uint32_t* value)
		{
			auto number = static_cast<Uint32>(0);
			auto size = context->read(context, &number, sizeof(Uint32), 1);
			*value = static_cast<uint32_t>(SDL_SwapBE32(number));
			return size * sizeof(Uint32);
		}
		inline const size_t read(int32_t* value)
		{
			auto number = static_cast<Uint32>(0);
			auto size = context->read(context, &number, sizeof(Uint32), 1);
			number = SDL_SwapBE32(number);
			*value = *reinterpret_cast<int32_t*>(&number);
			return size * sizeof(Uint32);
		}
		inline const size_t read(uint64_t* value)
		{
			auto number = static_cast<Uint64>(0);
			auto size = context->read(context, &number, sizeof(Uint64), 1);
			*value = static_cast<uint64_t>(SDL_SwapBE64(number));
			return size * sizeof(Uint64);
		}
		inline const size_t read(int64_t* value)
		{
			auto number = static_cast<Uint64>(0);
			auto size = context->read(context, &number, sizeof(Uint64), 1);
			number = SDL_SwapBE64(number);
			*value = *reinterpret_cast<int64_t*>(&number);
			return size * sizeof(Uint64);
		}
		inline const size_t read(float* value)
		{
			auto number = static_cast<float>(0);
			auto size = context->read(context, &number, sizeof(float), 1);
			*value = static_cast<float>(SDL_SwapFloatBE(number));
			return size * sizeof(float);
		}

		inline const size_t write(const void* values, const size_t size, const size_t count)
		{
			return context->write(context, values, size, count);
		}
		inline const size_t write(const void* values, const size_t count)
		{
			return context->write(context, values, 1, count);
		}
		inline const size_t write(const char* values, const size_t count)
		{
			return context->write(context, values, sizeof(char), count) * sizeof(char);
		}
		inline const size_t write(const uint8_t* values, const size_t count)
		{
			return context->write(context, values, sizeof(uint8_t), count) * sizeof(uint8_t);
		}
		inline const size_t write(const int8_t* values, const size_t count)
		{
			return context->write(context, values, sizeof(int8_t), count) * sizeof(int8_t);
		}
		inline const size_t write(const uint16_t* values, const size_t count)
		{
			auto size = static_cast<size_t>(0);
			auto number = static_cast<Uint16>(0);
			for (size_t i = 0; i < count; i++)
			{
				number = SDL_SwapBE16(static_cast<Uint16>(values[i]));
				size += context->write(context, &number, sizeof(Uint16), 1);
			}
			return size * sizeof(Uint16);
		}
		inline const size_t write(const uint32_t* values, const size_t count)
		{
			auto size = static_cast<size_t>(0);
			auto number = static_cast<Uint32>(0);
			for (size_t i = 0; i < count; i++)
			{
				number = SDL_SwapBE32(static_cast<Uint32>(values[i]));
				size += context->write(context, &number, sizeof(Uint32), 1);
			}
			return size * sizeof(Uint32);
		}
		inline const size_t write(const uint64_t* values, const size_t count)
		{
			auto size = static_cast<size_t>(0);
			auto number = static_cast<Uint64>(0);
			for (size_t i = 0; i < count; i++)
			{
				number = SDL_SwapBE64(static_cast<Uint64>(values[i]));
				size += context->write(context, &number, sizeof(Uint64), 1);
			}
			return size * sizeof(Uint64);
		}
		inline const size_t write(const uint8_t value)
		{
			return context->write(context, &value, sizeof(uint8_t), 1) * sizeof(int8_t);
		}
		inline const size_t write(const int8_t value)
		{
			return context->write(context, &value, sizeof(int8_t), 1) * sizeof(int8_t);
		}
		inline const size_t write(const uint16_t value)
		{
			auto number = SDL_SwapBE16(static_cast<Uint16>(value));
			return context->write(context, &number, sizeof(Uint16), 1) * sizeof(Uint16);
		}
		inline const size_t write(const int16_t value)
		{
			auto number = SDL_SwapBE16(*reinterpret_cast<Uint16*>(const_cast<int16_t*>(&value)));
			return context->write(context, &number, sizeof(Uint16), 1) * sizeof(Uint16);
		}
		inline const size_t write(const uint32_t value)
		{
			auto number = SDL_SwapBE32(static_cast<Uint32>(value));
			return context->write(context, &number, sizeof(Uint32), 1) * sizeof(Uint32);
		}
		inline const size_t write(const int32_t value)
		{
			auto number = SDL_SwapBE32(*reinterpret_cast<Uint32*>(const_cast<int32_t*>(&value)));
			return context->write(context, &number, sizeof(Uint32), 1) * sizeof(Uint32);
		}
		inline const size_t write(const uint64_t value)
		{
			auto number = SDL_SwapBE64(static_cast<Uint64>(value));
			return context->write(context, &number, sizeof(Uint64), 1) * sizeof(Uint64);
		}
		inline const size_t write(const int64_t value)
		{
			auto number = SDL_SwapBE64(*reinterpret_cast<Uint64*>(const_cast<int64_t*>(&value)));
			return context->write(context, &number, sizeof(Uint64), 1) * sizeof(Uint64);
		}
		inline const size_t write(const float value)
		{
			auto number = SDL_SwapFloatBE(static_cast<float>(value));
			return context->write(context, &number, sizeof(float), 1) * sizeof(float);
		}
	};
}
