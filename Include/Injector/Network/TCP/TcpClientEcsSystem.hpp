#pragma once
#include "Injector/ECS/EcsSystem.hpp"
#include "Injector/Network/TCP/TcpClient.hpp"
#include "Injector/Network/Datagram.hpp"

#include <mutex>

namespace Injector
{
	// Transfer Control Protocol client ECS system class
	class TcpClientEcsSystem :
		public EcsSystem,
		public TcpClient
	{
	 protected:
		// Maximal datagram buffer size
		size_t maxDatagramBufferSize;
		// Server response timeout time
		double responseTimeoutTime;
		// Received datagram buffer mutex
		std::mutex datagramBufferMutex;
		// Received datagram buffer
		std::vector<std::shared_ptr<Datagram>> datagramBuffer;

		// Message receive handle
		void onAsyncReceive(
			int byteCount) override;

		// Create datagram handle
		virtual std::shared_ptr<Datagram> createDatagram(
			const void* buffer,
			size_t byteCount) = 0;
		// Datagram receive handle
		virtual void onDatagramReceive(
			const std::shared_ptr<Datagram>& datagram) = 0;
		// Server response timeout handle
		virtual void onResponseTimeout();
	 public:
		// Creates and binds a new TCP client system
		explicit TcpClientEcsSystem(
			SocketFamily family,
			double responseTimeoutTime = 6.0,
			size_t maxDatagramBufferLength = 16,
			size_t receiveBufferSize = 8192);

		// Returns server receive timeout time
		double getTimeoutTime() const noexcept;
		// Sets server receive timeout time
		void setTimeoutTime(double time) noexcept;

		// Returns maximal received datagram buffer size
		size_t getMaxDatagramBufferSize() const noexcept;
		// Sets maximal received datagram buffer size
		void setMaxDatagramBufferSize(size_t size) noexcept;

		// Processes received datagrams
		void update() override;
	};
}
