#pragma once
#include <SDL_rwops.h>

#include <array>
#include <vector>

namespace inject
{
	struct UdpRequestResponse
	{
		inline static constexpr size_t headerSize = 1;

		inline void toBytes(void* buffer) const
		{
			auto context = SDL_RWFromMem(buffer, getSize());
			SDL_WriteU8(context, static_cast<Uint8>(getType()));
			toBytes(context);
			SDL_RWclose(context);
		}
		inline void toBytes(std::vector<uint8_t>& buffer) const
		{
			auto context = SDL_RWFromMem(buffer.data(), getSize());
			SDL_WriteU8(context, static_cast<Uint8>(getType()));
			toBytes(context);
			SDL_RWclose(context);
		}
		inline void fromBytes(const void* buffer)
		{
			auto context = SDL_RWFromConstMem(buffer, getSize());
			SDL_ReadU8(context);
			fromBytes(context);
			SDL_RWclose(context);
		}
		inline void fromBytes(const std::vector<uint8_t>& buffer)
		{
			auto context = SDL_RWFromConstMem(buffer.data(), getSize());
			SDL_ReadU8(context);
			fromBytes(context);
			SDL_RWclose(context);
		}

		virtual uint8_t getType() const = 0;
		virtual size_t getSize() const = 0;
		virtual void toBytes(SDL_RWops* context) const = 0;
		virtual void fromBytes(SDL_RWops* context) = 0;
	};
}
