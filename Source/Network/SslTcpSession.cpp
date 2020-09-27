#include "Injector/Network/SslTcpSession.hpp"
#include "Injector/Exception/NotImplementedException.hpp"

namespace Injector
{
	void SslTcpSession::endSession()
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
	SslTcpSession::~SslTcpSession()
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
