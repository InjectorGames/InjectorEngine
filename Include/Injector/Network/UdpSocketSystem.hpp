#pragma once
#include <inject/engine.hpp>
#include <inject/datagram.hpp>
#include <inject/udp_socket.hpp>

#include <entityx/entityx.h>

// TODO: refactor

namespace INJECT_NAMESPACE
{
	class UdpSocketSystem final :
		public UdpSocket,
		public entityx::System<UdpSocketSystem>,
		public entityx::Receiver<UdpSocketSystem>
	{
	public:
		using Buffer = std::string;
		using ReceiveHandler = std::function<void(
			const Endpoint&, MemoryStream&, const size_t)>;

		inline static constexpr size_t defaultBufferSize = 0xFFFF;
	private:
		Handler receiveHandler;
		Endpoint receiveEndpoint;
		Buffer receiveBuffer;
		MemoryStream receiveStream;
		MemoryStream sendStream;

		inline void async_receive_from()
		{
			UdpSocket::async_receive_from(
				receiveBuffer.data(), receiveBuffer.size(),
				receiveEndpoint, receiveHandler);
		}

		inline void handleReceive(
			ErrorCode error, size_t count)
		{
			if (!error)
			{
				try
				{
					const auto type = *reinterpret_cast<uint8_t*>(&receiveBuffer[0]);
					const auto& handler = receiveHandlers.at(static_cast<size_t>(type));
					receiveStream.str(receiveBuffer);
					receiveStream.seekg(1, std::ios::beg);
					handler(receiveEndpoint, receiveStream, count);
				}
				catch (const std::exception& exception)
				{
					inject::Engine::logError("Udp socket system receive exception: %s",
						exception.what());
				}
			}

			async_receive_from();
		}
	public:
		std::vector<ReceiveHandler> receiveHandlers;

		UdpSocketSystem(
			const std::shared_ptr<Context>& context = std::make_shared<Context>(),
			const Endpoint& localEndpoint = Endpoint(asio::ip::udp::v6(), defaultPort),
			const size_t bufferSize = defaultBufferSize) :
			UdpSocket(context, localEndpoint),
			receiveHandler(std::bind(&UdpSocketSystem::handleReceive,
				this, std::placeholders::_1, std::placeholders::_2)),
			receiveEndpoint(),
			receiveBuffer(defaultBufferSize, '\0'),
			receiveStream(),
			sendStream(),
			receiveHandlers()
		{}
		UdpSocketSystem(
			const std::shared_ptr<Context>& context = std::make_shared<Context>(),
			const uint16_t localPort = defaultPort,
			const size_t bufferSize = defaultBufferSize) :
			UdpSocket(context, localPort),
			receiveHandler(std::bind(&UdpSocketSystem::handleReceive,
				this, std::placeholders::_1, std::placeholders::_2)),
			receiveEndpoint(),
			receiveBuffer(defaultBufferSize, '\0'),
			receiveStream(),
			sendStream(),
			receiveHandlers()
		{}

		void configure(entityx::EntityManager& entities,
			entityx::EventManager& events) override
		{
			async_receive_from();
		}

		void update(entityx::EntityManager& entities,
			entityx::EventManager& events,
			entityx::TimeDelta deltaTime) override
		{}

		inline void send(const Datagram& datagram)
		{
			sendStream.seekp(std::ios::beg);
			datagram.toBytes(sendStream);
			const auto buffer = sendStream.str();
			UdpSocket::send(buffer.data(), datagram.getSize());
		}
		inline void send_to(const Datagram& datagram,
			const Endpoint& endpoint)
		{
			sendStream.seekp(std::ios::beg);
			datagram.toBytes(sendStream);
			const auto buffer = sendStream.str();
			UdpSocket::send_to(buffer.data(), datagram.getSize(), endpoint);
		}
	};
}
