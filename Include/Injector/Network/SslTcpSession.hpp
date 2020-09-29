#pragma once
#include "asio.hpp"
#include "asio/ssl.hpp"

namespace Injector
{
	class SslTcpSession
	{
	 protected:
		asio::ssl::stream<asio::ip::tcp::socket> stream;

		void endSession() noexcept;
		virtual void onSession();
	 public:
		explicit SslTcpSession(
			asio::ssl::stream<asio::ip::tcp::socket> stream);
		virtual ~SslTcpSession() = default;

		void onHandshake(const asio::error_code& error);
	};
}
