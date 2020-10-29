#include "Injector/Network/ClientSocketEcsSystem.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	void ClientSocketEcsSystem::onAsyncReceive(
		int byteCount)
	{
		datagramBufferMutex.lock();

		if(datagramBuffer.size() < maxDatagramBufferSize)
		{
			auto datagram = createDatagram(
				receiveBuffer.data(),
				receiveBuffer.size());

			datagramBuffer.push_back(
				std::move(datagram));
		}

		datagramBufferMutex.unlock();
	}

	ClientSocketEcsSystem::ClientSocketEcsSystem(
		SocketFamily family,
		SocketProtocol protocol,
		size_t _maxDatagramBufferSize,
		size_t receiveBufferSize) :
		ClientSocket(
			family,
			protocol,
			receiveBufferSize),
		maxDatagramBufferSize(_maxDatagramBufferSize),
		datagramBufferMutex(),
		datagramBuffer()
	{
	}

	size_t ClientSocketEcsSystem::getMaxDatagramBufferSize() const noexcept
	{
		return maxDatagramBufferSize;
	}
	void ClientSocketEcsSystem::setMaxDatagramBufferSize(size_t size) noexcept
	{
		maxDatagramBufferSize = size;
	}

	void ClientSocketEcsSystem::update()
	{
		if(!running)
			return;

		datagramBufferMutex.lock();

		for (int i = 0; i < datagramBuffer.size(); i++)
			onDatagramReceive(datagramBuffer[i]);

		datagramBuffer.clear();
		datagramBufferMutex.unlock();
	}
}
