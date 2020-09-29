#pragma once
 #include "Injector/Network/TcpSocket.hpp"

namespace Injector
{
	class TcpServer
	{
	 protected:
		std::shared_ptr<asio::io_context> context;
		asio::ip::tcp::acceptor acceptor;

		std::function<void(
			const asio::error_code&,
			asio::ip::tcp::socket)> acceptHandle;
	 public:
		explicit TcpServer(
			const std::function<void(
				const asio::error_code&,
				asio::ip::tcp::socket)>& acceptHandle,
			const std::shared_ptr<asio::io_context>& context =
				std::make_shared<asio::io_context>(),
			const asio::ip::tcp::endpoint& localEndpoint =
				TcpSocket::createEndpoint(TcpSocket::ipv6Any, 0));
		virtual ~TcpServer() = default;

		asio::ip::tcp::endpoint getLocalEndpoint() const noexcept;
		std::string getLocalAddress() const noexcept;
		uint16_t getLocalPort() const noexcept;

		void beginAccept();
	};
}
