#include "Injector/Network/UDP/UdpClientEcsSystem.hpp"
#include "Injector/Engine.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	void UdpClientEcsSystem::onAsyncReceive(
		int byteCount)
	{
		datagramBufferMutex.lock();

		if(datagramBuffer.size() < maxDatagramBufferSize)
		{
			auto datagram = createDatagram(
				receiveBuffer.data(),
				receiveBuffer.size());

			datagramBuffer.push_back(std::move(datagram));
			lastResponseTime = Engine::getTimeNow();
		}

		datagramBufferMutex.unlock();
	}

	void UdpClientEcsSystem::onResponseTimeout()
	{
		running = false;
	}

	UdpClientEcsSystem::UdpClientEcsSystem(
		SocketFamily family,
		double _responseTimeoutTime,
		size_t _maxDatagramBufferSize,
		size_t receiveBufferSize) :
		UdpClient(
			family,
			receiveBufferSize),
		responseTimeoutTime(_responseTimeoutTime),
		maxDatagramBufferSize(_maxDatagramBufferSize),
		datagramBufferMutex(),
		datagramBuffer()
	{
	}

	double UdpClientEcsSystem::getTimeoutTime() const noexcept
	{
		return responseTimeoutTime;
	}
	void UdpClientEcsSystem::setTimeoutTime(double time) noexcept
	{
		responseTimeoutTime = time;
	}

	size_t UdpClientEcsSystem::getMaxDatagramBufferSize() const noexcept
	{
		return maxDatagramBufferSize;
	}
	void UdpClientEcsSystem::setMaxDatagramBufferSize(size_t size) noexcept
	{
		maxDatagramBufferSize = size;
	}

	void UdpClientEcsSystem::update()
	{
		if(!running)
			return;

		if(Engine::getUpdateStartTime() - lastResponseTime > responseTimeoutTime)
		{
			onResponseTimeout();
			return;
		}

		datagramBufferMutex.lock();

		for (int i = 0; i < datagramBuffer.size(); i++)
			onDatagramReceive(datagramBuffer[i]);

		datagramBuffer.clear();
		datagramBufferMutex.unlock();
	}
}
