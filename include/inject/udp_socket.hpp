#pragma once
#include <inject/udp_request_response.hpp>

#include <SDL.h>
#include <SDL_net.h>

#include <string>
#include <stdexcept>

/*template <class Derived>
class UdpSocketSystem : public entityx::System<Derived>
{
protected:
	UDPsocket socket;
	std::vector<uint8_t> buffer;

	inline void sendTo(const UdpRequestResponse& requestResponse, const asio::ip::udp::endpoint& endpoint)
	{
		std::vector<uint8_t> buffer(requestResponse.getSize());
		requestResponse.toBytes(buffer);
		socket.send_to(asio::buffer(buffer), endpoint);
	}
	inline void asyncReceive()
	{
		socket.async_receive_from(asio::buffer(buffer), endpoint,
			std::bind(&UdpSocketSystem::handleReceive, this, std::placeholders::_1, std::placeholders::_2));
	}

	virtual void onReceive(const asio::error_code& error, const size_t count) = 0;

	inline void handleReceive(const asio::error_code& error, size_t count)
	{
		onReceive(error, count);
	}
public:
	UdpSocketSystem(const uint16_t port = 0,
		const size_t bufferSize = 0xFFFF) :
		buffer(bufferSize)
	{
		udpsock = SDLNet_UDP_Open(static_cast<Uint16>(port));

		if (!udpsock)
			throw std::runtime_error("Failed to open UDP socket. Error: " + std::string(SDLNet_GetError()));
	}
};*/

namespace inject
{
	class UdpSocket
	{
	protected:
		UDPsocket socket;
	public:
		UdpSocket(const uint16_t port = 0)
		{
			socket = SDLNet_UDP_Open(static_cast<Uint16>(port));

			if (!socket)
				throw std::runtime_error("Failed to open UDP socket. Error: " + std::string(SDLNet_GetError()));
		}
		virtual ~UdpSocket()
		{
			SDLNet_UDP_Close(socket);
			socket = nullptr;
		}

		inline void send()
		{
			auto packet = SDLNet_AllocPacket(1024);
		}
	};
}
