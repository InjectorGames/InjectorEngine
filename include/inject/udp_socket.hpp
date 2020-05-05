#pragma once
#include <entityx/entityx.h>
#include <asio.hpp>

#include <vector>
#include <cstdlib>

namespace njng
{
	template <class Derived>
	class UdpSocket : public entityx::System<Derived>
	{
	protected:
		asio::ip::udp::socket m_socket;
		asio::ip::udp::endpoint m_endpoint;
		std::vector<uint8_t> m_buffer;

		inline void asyncReceive()
		{
			m_socket.async_receive_from(asio::buffer(m_buffer), m_endpoint, std::bind(&UdpSocket::handleReceive, this, std::placeholders::_1, std::placeholders::_2));
		}

		virtual void onReceive(const asio::error_code& error, size_t count) = 0;

		inline void handleReceive(const asio::error_code& error, size_t count)
		{
			onReceive(error, count);
		}
	public:
		UdpSocket(asio::io_context& context, uint16_t port = 0) :
			m_socket(context, asio::ip::udp::endpoint(asio::ip::udp::v6(), port)),
			m_endpoint(),
			m_buffer(0xFFFF)
		{
			asyncReceive();
		}
	};
}