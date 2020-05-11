#pragma once
#include <starnet/datagram_type.hpp>
#include <inject/udp_request_response.hpp>

namespace starnet
{
	struct UdpPingResponse final : inject::UdpRequestResponse
	{
		inline static constexpr size_t size =
			headerSize + sizeof(uint32_t) * 2;

		uint32_t playerCount;
		uint32_t maxPlayerCount;

		UdpPingResponse(const uint32_t _playerCount,
			const uint32_t _maxPlayerCount) :
			playerCount(_playerCount),
			maxPlayerCount(_maxPlayerCount)
		{}
		UdpPingResponse(const std::vector<uint8_t>& buffer, const size_t count)
		{
			if (count != UdpPingResponse::size)
				throw std::runtime_error("Incorrect Ping response size");

			inject::UdpRequestResponse::fromBytes(buffer.data(), count);
		}

		size_t getSize() const override
		{
			return size;
		}
		void toBytes(SDL_RWops* context) const override
		{
			SDL_WriteU8(context, static_cast<Uint8>(DatagramType::Ping));
			SDL_WriteBE32(context, static_cast<Uint32>(playerCount));
			SDL_WriteBE32(context, static_cast<Uint32>(maxPlayerCount));
		}
		void fromBytes(SDL_RWops* context) override
		{
			SDL_ReadU8(context);
			playerCount = static_cast<uint32_t>(SDL_ReadBE32(context));
			maxPlayerCount = static_cast<uint32_t>(SDL_ReadBE32(context));
		}
	};
}
