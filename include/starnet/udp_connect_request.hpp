#pragma once
#include <starnet/datagram_type.hpp>
#include <inject/udp_request_response.hpp>

#include <string>
#include <stdexcept>

namespace starnet
{
	struct UdpConnectRequest final : inject::UdpRequestResponse
	{
		inline static constexpr size_t usernameSize = 16;

		inline static bool isValidUsername(const std::string& username)
		{
			if (username.size() != usernameSize)
				return false;

			for (size_t i = 0; i < username.size(); i++)
			{
				auto value = username[i];

				if (value < 48 || value > 57 && value < 97 && value != 95 || value > 122)
					return false;
			}

			return true;
		}

		inline static const size_t size = headerSize + usernameSize;

		std::string username;

		UdpConnectRequest(const std::string& _username) :
			username(_username)
		{
			if (!isValidUsername(username))
				throw std::runtime_error("Invalid username value");
		}
		UdpConnectRequest(const std::vector<uint8_t>& buffer)
		{
			inject::UdpRequestResponse::fromBytes(buffer);

			if (!isValidUsername(username))
				throw std::runtime_error("Invalid username value");
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
			SDL_RWwrite(context, username.data(), sizeof(char), username.size());
		}
		void fromBytes(SDL_RWops* context) override
		{
			username = std::string(usernameSize, ' ');
			SDL_RWread(context, username.data(), sizeof(char), username.size());
		}
	};
}