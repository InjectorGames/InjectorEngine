#include "Injector/Network/TCP/TcpClient.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	TcpClient::TcpClient(
		SocketFamily family,
		double _responseTimeoutTime,
		size_t _receiveBufferSize) :
		socket(family, SocketProtocol::TCP),
		socketConnect(SocketConnect::Disconnected),
		responseTimeoutTime(_responseTimeoutTime),
		lastResponseTime(0.0),
		receiveBuffer(_receiveBufferSize),
		sendBuffer()
	{
		auto localEndpoint = Endpoint();

		if (family == SocketFamily::IPv4)
		{
			localEndpoint = Endpoint::anyIPv4;
		}
		else if (family == SocketFamily::IPv6)
		{
			localEndpoint = Endpoint::anyIPv6;
		}
		else
		{
			throw Exception(
				std::string(typeid(TcpClient).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Unspecified socket family");
		}

		socket.bind(localEndpoint);
	}



	// TODO: TCP client first connect stage and then receive stage on thread
}