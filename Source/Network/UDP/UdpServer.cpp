#include "Injector/Network/UDP/UdpServer.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	void UdpServer::asyncReceiveHandle()
	{
		while(running)
		{
			auto endpoint = Endpoint();

			auto byteCount = socket.receiveFrom(
				receiveBuffer, 
				endpoint);

			if(byteCount > 0)
				onAsyncReceive(byteCount);
		}
	}

	UdpServer::UdpServer(
		SocketFamily family,
		const std::string& port,
		size_t _receiveBufferSize) :
		socket(family, SocketProtocol::UDP),
		running(false),
		receiveThread(),
		receiveBuffer(_receiveBufferSize),
		sendBuffer()
	{
		auto localEndpoint = Endpoint();

		if (family == SocketFamily::IPv4)
		{
			localEndpoint = Endpoint(
				Endpoint::anyAddressIPv4,
				port);
		}
		else if (family == SocketFamily::IPv6)
		{
			localEndpoint = Endpoint(
				Endpoint::anyAddressIPv6,
				port);
		}
		else
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Unspecified socket family");
		}

		socket.bind(localEndpoint);
	}

	const Socket& UdpServer::getSocket() const noexcept
	{
		return socket;
	}
	bool UdpServer::isRunning() const noexcept
	{
		return running;
	}

	void UdpServer::start()
	{
		if(running)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Server is already running");
		}

		running = true;

		receiveThread = std::thread(
			&UdpServer::asyncReceiveHandle,
			this);
	}
	int UdpServer::sendTo(
		const Datagram& datagram,
		const Endpoint& endpoint)
	{
		auto byteSize = datagram.getByteSize();

		if(sendBuffer.size() < byteSize)
			sendBuffer.resize(byteSize);

		datagram.writeData(sendBuffer.data());

		return socket.sendTo(
			sendBuffer,
			endpoint);
	}
}
