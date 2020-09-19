#pragma once
#include <vector>
#include <cstdint>

namespace Injector
{
	class Compressor
	{
	 public:
		static int getCompressSize(int sourceSize);

		static int compress(
			const void* source,
			int sourceSize,
			void* destination,
			int destinationSize);
		static int decompress(
			const void* source,
			int sourceSize,
			void* destination,
			int destinationSize);

		template<class T = uint8_t>
		static std::vector<T> compress(const void* source, int size)
		{
			auto compressSize = getCompressSize(size);
			auto destination = new std::vector<T>(compressSize / sizeof(T));
			auto count = compress(source, size,
				destination.data(), compressSize);
			destination.resize(count / sizeof(T));
			return destination;
		}
		template<class DT = uint8_t, class ST = uint8_t>
		static std::vector<DT> compress(const std::vector<ST>& source)
		{
			auto compressSize = getCompressSize(source.size() * sizeof(ST));
			auto destination = new std::vector<DT>(compressSize / sizeof(DT));
			auto count = compress(source.data(), source.size() * sizeof(ST),
				destination.data(), compressSize);
			destination.resize(count / sizeof(DT));
			return destination;
		}
	};
}
