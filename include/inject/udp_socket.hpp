#pragma once
#include <inject/udp_request_response.hpp>
#include <asio.hpp>

namespace inject
{
	class UdpSocket
	{
	protected:
		std::shared_ptr<asio::io_context> context;
		asio::ip::udp::socket socket;
	public:
		UdpSocket(
			const std::shared_ptr<asio::io_context>& _context,
			const uint16_t port = 0) :
			context(_context),
			socket(*_context, asio::ip::udp::endpoint(asio::ip::udp::v6(), port))
		{}

		inline void connect(const asio::ip::udp::endpoint& endpoint)
		{
			socket.connect(endpoint);
		}

		inline void asyncReceive(void* buffer, const size_t size,
			std::function<void(const asio::error_code&, size_t)>& callback)
		{
			socket.async_receive(asio::buffer(buffer, size), callback);
		}
		inline void asyncReceive(std::vector<uint8_t>& buffer,
			std::function<void(const asio::error_code&, size_t)>& callback)
		{
			socket.async_receive(asio::buffer(buffer), callback);
		}

		inline void asyncReceiveFrom(void* buffer, const size_t size,
			asio::ip::udp::endpoint& endpoint,
			std::function<void(const asio::error_code&, size_t)>& callback)
		{
			socket.async_receive_from(asio::buffer(buffer, size), endpoint, callback);
		}
		inline void asyncReceiveFrom(std::vector<uint8_t>& buffer,
			asio::ip::udp::endpoint& endpoint,
			std::function<void(const asio::error_code&, size_t)>& callback)
		{
			socket.async_receive_from(asio::buffer(buffer), endpoint, callback);
		}

		inline void sendTo(const void* buffer, const size_t size,
			const asio::ip::udp::endpoint& endpoint)
		{
			socket.send_to(asio::buffer(buffer, size), endpoint);
		}
		inline void sendTo(const std::vector<uint8_t>& buffer,
			const asio::ip::udp::endpoint& endpoint)
		{
			socket.send_to(asio::buffer(buffer), endpoint);
		}
		inline void sendTo(const UdpRequestResponse& requestResponse,
			const asio::ip::udp::endpoint& endpoint)
		{
			auto size = requestResponse.getSize();
			auto buffer = new uint8_t[size];
			requestResponse.toBytes(buffer, size);
			socket.send_to(asio::buffer(buffer, size), endpoint);
			delete[] buffer;
		}

		inline void send(const void* buffer, const size_t size)
		{
			socket.send(asio::buffer(buffer, size));
		}
		inline void send(const std::vector<uint8_t>& buffer)
		{
			socket.send(asio::buffer(buffer));
		}
		inline void send(const UdpRequestResponse& requestResponse)
		{
			auto size = requestResponse.getSize();
			auto buffer = new uint8_t[size];
			requestResponse.toBytes(buffer, size);
			socket.send(asio::buffer(buffer, size));
			delete[] buffer;
		}
	};
}
