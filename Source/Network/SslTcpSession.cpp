#include "Injector/Network/SslTcpSession.hpp"

namespace Injector
{
	void SslTcpSession::endSession() noexcept
	{
		delete this;
	}
	void SslTcpSession::onSession()
	{
		endSession();
	}

	SslTcpSession::SslTcpSession(
		asio::ssl::stream<asio::ip::tcp::socket> _stream) :
		stream(std::move(_stream))
	{
	}

	void SslTcpSession::onHandshake(
		const asio::error_code& error)
	{
		if(error)
			return;

		onSession();
	}
}
