#include "Injector/Network/Datagram.hpp"

namespace Injector
{
	Datagram::Datagram(
		uint8_t _type,
		bool _valid) noexcept :
		type(_type),
		valid(_valid)
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
