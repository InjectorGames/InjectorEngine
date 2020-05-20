#pragma once
#include <inject/stream.hpp>

namespace inject
{
	class FileStream : public Stream
	{
	public:
		FileStream(const std::string& filePath,
			const std::string& mode) :
			Stream(SDL_RWFromFile(filePath.c_str(), mode.c_str()))
		{
			if (!context)
				throw std::runtime_error(
					"Failed to create file stream. Error: " +
					std::string(SDL_GetError()));
		}
		virtual ~FileStream()
		{
			context->close(context);
		}
	};
}
