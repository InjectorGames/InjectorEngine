#pragma once
#include <inject/stream.hpp>

namespace inject
{
	class MemoryStream : public Stream
	{
	public:
		MemoryStream(void* const buffer,
			const size_t size) :
			Stream(SDL_RWFromMem(buffer, size))
		{
			if (!context)
				throw std::runtime_error(
					"Failed to create memory stream. Error: " +
					std::string(SDL_GetError()));
		}
		MemoryStream(const void* const buffer,
			const size_t size) :
			Stream(SDL_RWFromConstMem(buffer, size))
		{
			if (!context)
				throw std::runtime_error(
					"Failed to create memory stream. Error: " +
					std::string(SDL_GetError()));
		}
		virtual ~MemoryStream()
		{
			context->close(context);
		}
	};
}
