#include "Injector/Network/TCP/TcpClientEcsSystem.hpp"
#include "Injector/Engine.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	void TcpClientEcsSystem::onAsyncReceive(
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

	void TcpClientEcsSystem::onResponseTimeout()
	{
		running = false;
	}

	TcpClientEcsSystem::TcpClientEcsSystem(
		SocketFamily family,
		double _responseTimeoutTime,
		size_t _maxDatagramBufferSize,
		size_t receiveBufferSize) :
		TcpClient(
			family,
			receiveBufferSize),
		responseTimeoutTime(_responseTimeoutTime),
		maxDatagramBufferSize(_maxDatagramBufferSize),
		datagramBufferMutex(),
		datagramBuffer()
	{
	}

	double TcpClientEcsSystem::getTimeoutTime() const noexcept
	{
		return responseTimeoutTime;
	}
	void TcpClientEcsSystem::setTimeoutTime(double time) noexcept
	{
		responseTimeoutTime = time;
	}

	size_t TcpClientEcsSystem::getMaxDatagramBufferSize() const noexcept
	{
		return maxDatagramBufferSize;
	}
	void TcpClientEcsSystem::setMaxDatagramBufferSize(size_t size) noexcept
	{
		maxDatagramBufferSize = size;
	}

	void TcpClientEcsSystem::update()
	{
		datagramBufferMutex.lock();

		if(!running)
			return;

		if(Engine::getUpdateStartTime() - lastResponseTime > responseTimeoutTime)
		{
			onResponseTimeout();
			return;
		}

		for (int i = 0; i < datagramBuffer.size(); i++)
			onDatagramReceive(datagramBuffer[i]);

		datagramBuffer.clear();
		datagramBufferMutex.unlock();
	}
}
