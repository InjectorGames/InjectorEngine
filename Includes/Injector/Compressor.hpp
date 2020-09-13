#pragma once
#include <inject/defines.hpp>

#include <zlib.h>

#include <stdio.h>

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif


// TODO:


namespace INJECT_NAMESPACE
{
	class Compressor
	{
	public:
		inline static const int compress(
			FILE* source, FILE* dest, int level = -1)
		{
			z_stream strm;
			strm.zalloc = Z_NULL;
			strm.zfree = Z_NULL;
			strm.opaque = Z_NULL;
			auto ret = deflateInit(&strm, level);
			if (ret != Z_OK)
				return ret;
		}
	};
}
