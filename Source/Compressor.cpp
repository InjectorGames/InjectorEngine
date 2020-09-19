#include "Injector/Compressor.hpp"
#include "Injector/Exception/OutOfRangeException.hpp"

#include "lz4.h"

namespace Injector
{
	int Compressor::getCompressSize(int sourceSize)
	{
		auto count = LZ4_compressBound(sourceSize);

		if (count == 0)
		{
			throw Exception(
				"Compressor",
				"getDestinationSize",
				"Incorrect input");
		}

		return count;
	}
	int Compressor::compress(
		const void* source,
		int sourceSize,
		void* destination,
		int destinationSize)
	{
		auto count = LZ4_compress_default(
			reinterpret_cast<const char*>(source),
			reinterpret_cast<char*>(destination),
			sourceSize,
			destinationSize);

		if (count == 0)
		{
			throw Exception(
				"Compressor",
				"compress",
				"Failed to compress");
		}

		return count;
	}
	int Compressor::decompress(
		const void* source,
		int sourceSize,
		void* destination,
		int destinationSize)
	{
		auto count = LZ4_decompress_safe(
			reinterpret_cast<const char*>(source),
			reinterpret_cast<char*>(destination),
			sourceSize,
			destinationSize);

		if (count < 1)
		{
			throw Exception(
				"Compressor",
				"compress",
				"Failed to decompress");
		}

		return count;
	}
}
