#pragma once
#include <starnet/datagram_type.hpp>
#include <inject/udp_request_response.hpp>

namespace starnet
{
	struct UdpConnectResponse final : inject::UdpRequestResponse
	{
		enum Result : uint8_t
		{
			Connected,
			SeverIsFull,
		};

		inline static constexpr size_t size = headerSize + sizeof(uint8_t);

		uint8_t result;

		UdpConnectResponse(const uint8_t _result) :
			result(_result)
		{}
		UdpConnectResponse(const std::vector<uint8_t>& buffer)
		{
			inject::UdpRequestResponse::fromBytes(buffer);
		}

		uint8_t getType() const
		{
			return static_cast<uint8_t>(DatagramType::Connect);
		}
		size_t getSize() const override
		{
			return size;
		}
		void toBytes(SDL_RWops* context) const override
		{
			SDL_WriteU8(context, static_cast<Uint8>(result));
		}
		void fromBytes(SDL_RWops* context) override
		{
			result = static_cast<uint8_t>(SDL_ReadU8(context));
		}
	};
}
