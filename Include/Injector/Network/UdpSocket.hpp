#pragma once
#include <inject/defines.hpp>
#include <asio.hpp>

// TODO: refactor

namespace INJECT_NAMESPACE
{
	class UdpSocket : public asio::ip::udp::socket
	{
	 public:
		using Context = asio::io_context;
		using ErrorCode = asio::error_code;
		using Socket = asio::ip::udp::socket;
		using Endpoint = asio::ip::udp::endpoint;
		using Handler = std::function<void(const ErrorCode&, size_t)>;

		inline static constexpr uint16_t defaultPort = 0;
	 protected:
		std::shared_ptr<Context> context;
	 public:
		UdpSocket(
			const std::shared_ptr<Context>& _context =
				std::make_shared<Context>(),
			const Endpoint& localEndpoint =
				Endpoint(asio::ip::udp::v6(), defaultPort)) :
			asio::ip::udp::socket(*_context, localEndpoint),
			context(_context)
		{
		}
		UdpSocket(
			const std::shared_ptr<Context>& _context = std::make_shared<Context>(),
			const uint16_t localPort = defaultPort) :
			asio::ip::udp::socket(*_context, Endpoint(asio::ip::udp::v6(), localPort)),
			context(_context)
		{
		}
		virtual ~UdpSocket()
		{
		}

		inline const std::shared_ptr<Context>& getContext() const noexcept
		{
			return context;
		}

		inline const size_t receive(
			void* buffer,
			const size_t size)
		{
			return Socket::receive(asio::buffer(buffer, size));
		}
		inline const size_t receive_from(
			void* buffer,
			const size_t size,
			Endpoint& endpoint)
		{
			return Socket::receive_from(asio::buffer(buffer, size), endpoint);
		}

		inline void async_receive(
			void* buffer,
			const size_t size,
			Handler& handler)
		{
			Socket::async_receive(asio::buffer(buffer, size), handler);
		}
		inline void async_receive_from(
			void* buffer,
			const size_t size,
			Endpoint& endpoint,
			Handler& handler)
		{
			Socket::async_receive_from(asio::buffer(buffer, size), endpoint, handler);
		}

		inline const size_t send(
			const void* buffer,
			const size_t size)
		{
			return Socket::send(asio::buffer(buffer, size));
		}
		inline const size_t send_to(
			const void* buffer,
			const size_t size,
			const Endpoint& endpoint)
		{
			return Socket::send_to(asio::buffer(buffer, size), endpoint);
		}

		inline void async_send(
			const void* buffer,
			const size_t size,
			Handler& handler)
		{
			Socket::async_send(asio::buffer(buffer, size), handler);
		}
		inline void async_send_to(
			const void* buffer,
			const size_t size,
			Endpoint& endpoint,
			Handler& handler)
		{
			Socket::async_send_to(asio::buffer(buffer, size), endpoint, handler);
		}
	};
}
