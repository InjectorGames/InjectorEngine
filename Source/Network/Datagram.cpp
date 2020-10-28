#include "Injector/Network/Datagram.hpp"

namespace Injector
{
	Datagram::Datagram(
		uint8_t _type) :
		type(_type),
		valid(false)
	{
	}

	uint8_t Datagram::getType() const noexcept
	{
		return type;
	}
	bool Datagram::isValid() const noexcept
	{
		return valid;
	}
}
