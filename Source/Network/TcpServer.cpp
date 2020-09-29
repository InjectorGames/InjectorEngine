#include "Injector/Network/TcpServer.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	TcpServer::TcpServer(
		const std::function<void(
			const asio::error_code&,
			asio::ip::tcp::socket)>& _acceptHandle,
		const std::shared_ptr<asio::io_context>& _context,
		const asio::ip::tcp::endpoint& localEndpoint) :
		context(_context),
		acceptor(*context, localEndpoint),
		acceptHandle(_acceptHandle)
	{
		if(!_context)
		{
			throw NullException(
				"TcpServer",
				"TcpServer",
				"context");
		}
		if(!_acceptHandle)
		{
			throw NullException(
				"TcpServer",
				"TcpServer",
				"acceptHandle");
		}
	}

	asio::ip::tcp::endpoint TcpServer::getLocalEndpoint() const noexcept
	{
		return acceptor.local_endpoint();
	}
	std::string TcpServer::getLocalAddress() const noexcept
	{
		return acceptor.local_endpoint().address().to_string();
	}
	uint16_t TcpServer::getLocalPort() const noexcept
	{
		return acceptor.local_endpoint().port();
	}

	void TcpServer::beginAccept()
	{
		acceptor.async_accept(acceptHandle);
	}
}
