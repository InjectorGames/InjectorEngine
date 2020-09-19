#include "Injector/Network/Datagram.hpp"
#include "Injector/Exception/NotImplementedException.hpp"

namespace Injector
{
	Datagram::~Datagram()
	{
	}
	size_t Datagram::getSize() const
	{
		throw NotImplementedException("Datagram", "getSize");
	}
	void Datagram::toBytes(MemoryStream& stream) const
	{
		throw NotImplementedException("Datagram", "toBytes");
	}
	void Datagram::fromBytes(MemoryStream& stream)
	{
		throw NotImplementedException("Datagram", "fromBytes");
	}
}
