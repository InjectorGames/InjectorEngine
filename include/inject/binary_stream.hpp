#pragma once
#include <asio.hpp>

#include <array>
#include <cstdint>

namespace njng
{
	class BinaryStream
	{
	protected:
		size_t m_index;
		size_t m_size;
		uint8_t* m_buffer;
	public:
		BinaryStream(const size_t size) :
			m_index(0),
			m_size(size),
			m_buffer(new uint8_t[size])
		{}
		virtual ~BinaryStream()
		{
			delete[] m_buffer;
			m_buffer = nullptr;
		}

		inline void write(const uint8_t value)
		{
			m_buffer[m_index++] = value;
		}
		inline void write(const int8_t value)
		{
			m_buffer[m_index++] = static_cast<uint8_t>(value);
		}
		inline void write(const uint16_t value)
		{
			
			m_buffer[m_index++] = static_cast<uint8_t>(value);
		}

		inline uint8_t read()
		{
			return m_buffer[m_index--];
		}
		inline int8_t read()
		{
			return static_cast<int8_t>(m_buffer[m_index--]);
		}

		inline static bool isBigEndian()
		{
			return 0x1234 == asio::detail::socket_ops::host_to_network_short(0x1234);
		}
	};
}
