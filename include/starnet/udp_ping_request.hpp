#pragma once
#include <starnet/datagram_type.hpp>
#include <inject/udp_request_response.hpp>

namespace starnet
{
	struct UdpPingRequest final : inject::UdpRequestResponse
	{
		inline static constexpr size_t size = headerSize;

		UdpPingRequest(const std::vector<uint8_t>& buffer, const size_t count)
		{
			if (count != UdpPingRequest::size)
				throw std::runtime_error("Incorrect Ping request size");

			inject::UdpRequestResponse::fromBytes(buffer.data(), count);
		}

		size_t getSize() const override
		{
			return size;
		}
		void toBytes(SDL_RWops* context) const override
		{
			SDL_WriteU8(context, static_cast<Uint8>(DatagramType::Ping));
		}
		void fromBytes(SDL_RWops* context) override
		{
			SDL_ReadU8(context);
		}
	};
}
