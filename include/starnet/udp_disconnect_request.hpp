#pragma once
#include <starnet/datagram_type.hpp>
#include <inject/udp_request_response.hpp>

namespace starnet
{
	struct UdpDisconnectRequest final : inject::UdpRequestResponse
	{
		enum Reason : uint8_t
		{
			Requested,
		};

		inline static constexpr size_t size = headerSize + sizeof(uint8_t);

		uint8_t reason;

		UdpDisconnectRequest(const uint8_t _reason) :
			reason(_reason)
		{}
		UdpDisconnectRequest(const std::vector<uint8_t>& buffer, const size_t count)
		{
			if (count != UdpConnectRequest::size)
				throw std::runtime_error("Incorrect request size");

			inject::UdpRequestResponse::fromBytes(buffer.data(), count);
		}

		size_t getSize() const override
		{
			return size;
		}
		void toBytes(SDL_RWops* context) const override
		{
			SDL_WriteU8(context, static_cast<Uint8>(DatagramType::Disconnect));
			SDL_WriteU8(context, static_cast<Uint8>(reason));
		}
		void fromBytes(SDL_RWops* context) override
		{
			SDL_ReadU8(context);
			reason = static_cast<uint8_t>(SDL_ReadU8(context));
		}
	};
}