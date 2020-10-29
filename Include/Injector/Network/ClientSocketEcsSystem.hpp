#pragma once
#include "Injector/ECS/EcsSystem.hpp"
#include "Injector/Network/ClientSocket.hpp"
#include "Injector/Network/Datagram.hpp"

#include <mutex>

namespace Injector
{
	// Client socket ECS system class
	class ClientSocketEcsSystem :
		public EcsSystem,
		public ClientSocket
	{
	 protected:
		// Maximal datagram buffer size
		size_t maxDatagramBufferSize;
		// Received datagram buffer mutex
		std::mutex datagramBufferMutex;
		// Received datagram buffer
		std::vector<std::shared_ptr<Datagram>> datagramBuffer;

		// Asynchronous message receive handle
		void onAsyncReceive(int byteCount) override;

		// Create datagram handle
		virtual std::shared_ptr<Datagram> createDatagram(
			const void* buffer,
			size_t byteCount) = 0;
		// Datagram receive handle
		virtual void onDatagramReceive(
			const std::shared_ptr<Datagram>& datagram) = 0;
	 public:
		// Creates and binds a new client socket ECS system
		explicit ClientSocketEcsSystem(
			SocketFamily family,
			SocketProtocol protocol,
			size_t maxDatagramBufferSize = 16,
			size_t receiveBufferSize = 8192);

		// Returns maximal received datagram buffer size
		size_t getMaxDatagramBufferSize() const noexcept;
		// Sets maximal received datagram buffer size
		void setMaxDatagramBufferSize(size_t size) noexcept;

		// Processes received datagrams
		void update() override;
	};
}