#pragma once
#include <asio.hpp>

#include <array>
#include <cstdint>

namespace njng
{
	class BinaryStream
	{
	protected:
		size_t index;
		size_t size;
		uint8_t* buffer;
	public:
		BinaryStream(const size_t _size) :
			index(0),
			size(_size),
			buffer(new uint8_t[_size])
		{}
		virtual ~BinaryStream()
		{
			delete[] m_buffer;
			m_buffer = nullptr;
		}

		inline void write(const uint8_t value)
		{
			buffer[index++] = value;
		}
		inline void write(const int8_t value)
		{
			buffer[index++] = static_cast<uint8_t>(value);
		}
		inline void write(const uint16_t value)
		{
			// TODO:
			buffer[index++] = static_cast<uint8_t>(value);
		}

		inline uint8_t read()
		{
			return buffer_index--];
		}
		inline int8_t read()
		{
			return static_cast<int8_t>(buffer[index--]);
		}

		inline static bool isBigEndian()
		{
			return 0x1234 == asio::detail::socket_ops::host_to_network_short(0x1234);
		}
	};
}
