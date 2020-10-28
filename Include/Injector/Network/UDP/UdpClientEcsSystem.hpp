#pragma once
#include "Injector/ECS/EcsSystem.hpp"
#include "Injector/Network/UDP/UdpClient.hpp"
#include "Injector/Network/Datagram.hpp"
#include "Injector/Network/DatagramFactory.hpp"

namespace Injector
{
	// User Datagram Protocol client ECS system class
	class UdpClientEcsSystem :
		public EcsSystem,
		public UdpClient
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
		// Creates and binds a new UDP client ECS system
		UdpClientEcsSystem(
			SocketFamily family,
			double responseTimeoutTime = 6.0,
			size_t maxDatagramBufferLength = 16,
			size_t receiveBufferSize = 8192);

		// Returns client receive timeout time
		double getTimeoutTime() const noexcept;
		// Sets client receive timeout time
		void setTimeoutTime(double time) noexcept;

		// Returns maximal received datagram buffer size
		size_t getMaxDatagramBufferSize() const noexcept;
		// Sets maximal received datagram buffer size
		void setMaxDatagramBufferSize(size_t size) noexcept;

		// Executes on each update cycle
		void update() override;
	};
}
