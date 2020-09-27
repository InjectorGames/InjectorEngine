#include "Injector/Network/TcpServer.hpp"
#include "Injector/Network/SslTcpSession.hpp"

namespace Injector
{
	class SslTcpServer : public TcpServer
	{
	 protected:
		std::shared_ptr<asio::ssl::context> sslContext;
		std::function<SslTcpSession*(asio::ssl::stream<
		    asio::ip::tcp::socket>)> sessionFactory;

		void onAccept(
			const asio::error_code& error,
			asio::ip::tcp::socket socket);

		friend class SslTcpSession;
	 public:
		SslTcpServer(
			const std::function<SslTcpSession*(asio::ssl::stream<
			    asio::ip::tcp::socket>)>& sessionFactory,
			const std::shared_ptr<asio::io_context>& context =
				std::make_shared<asio::io_context>(),
			const std::shared_ptr<asio::ssl::context>& sslContext =
				std::make_shared<asio::ssl::context>(asio::ssl::context::tlsv13_server),
			const asio::ip::tcp::endpoint& localEndpoint =
				TcpSocket::createEndpoint(TcpSocket::ipv6Any, 0));
		virtual ~SslTcpServer();
	};
}