#include "Injector/Network/SslTcpServer.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	void SslTcpServer::onAccept(
		const asio::error_code& error,
		asio::ip::tcp::socket socket)
	{
		if(error)
			return;

		auto stream = asio::ssl::stream<asio::ip::tcp::socket>(
			std::move(socket),
			*sslContext);
		auto session = sessionFactory(
			std::move(stream));
		auto handshakeHandle = std::bind(
			&SslTcpSession::onHandshake,
			session,
			std::placeholders::_1);
		stream.async_handshake(
			asio::ssl::stream_base::server,
			handshakeHandle);
	}

	SslTcpServer::SslTcpServer(
		const std::function<SslTcpSession*(asio::ssl::stream<
		    asio::ip::tcp::socket>)>& _sessionFactory,
		const std::shared_ptr<asio::io_context>& context,
		const std::shared_ptr<asio::ssl::context>& _sslContext,
		const asio::ip::tcp::endpoint& localEndpoint) :
		TcpServer(
			std::bind(
				&SslTcpServer::onAccept,
				this,
				std::placeholders::_1,
				std::placeholders::_2),
			context,
			localEndpoint),
		sslContext(_sslContext),
		sessionFactory(_sessionFactory)
	{
		if(!_sslContext)
		{
			throw NullException(
				"SslTcpServer",
				"SslTcpServer",
				"sslContext");
		}
		if(!_sessionFactory)
		{
			throw NullException(
				"SslTcpServer",
				"SslTcpServer",
				"sessionFactory");
		}
	}
}
