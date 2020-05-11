#pragma once
#include <SDL_rwops.h>

#include <array>
#include <vector>

namespace inject
{
	struct UdpRequestResponse
	{
		inline static constexpr size_t headerSize = 1;

		inline void toBytes(void* buffer, const size_t count) const
		{
			auto context = SDL_RWFromMem(buffer, count);
			toBytes(context);
			SDL_RWclose(context);
		}
		inline void fromBytes(const void* buffer, const size_t count)
		{
			auto context = SDL_RWFromConstMem(buffer, count);
			fromBytes(context);
			SDL_RWclose(context);
		}

		virtual size_t getSize() const = 0;
		virtual void toBytes(SDL_RWops* context) const = 0;
		virtual void fromBytes(SDL_RWops* context) = 0;
	};
}
