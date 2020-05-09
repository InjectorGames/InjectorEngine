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
		asio::ip::udp::socket socket;
		asio::ip::udp::endpoint endpoint;
		std::vector<uint8_t> buffer;

		inline void asyncReceive()
		{
			socket.async_receive_from(asio::buffer(buffer), endpoint, std::bind(&UdpSocket::handleReceive, this, std::placeholders::_1, std::placeholders::_2));
		}

		virtual void onReceive(const asio::error_code& error, const size_t count) = 0;

		inline void handleReceive(const asio::error_code& error, size_t count)
		{
			onReceive(error, count);
		}
	public:
		UdpSocket(asio::io_context& context, const uint16_t port = 0) :
			socket(context, asio::ip::udp::endpoint(asio::ip::udp::v6(), port)),
			endpoint(),
			buffer(0xFFFF)
		{
			asyncReceive();
		}
	};
}