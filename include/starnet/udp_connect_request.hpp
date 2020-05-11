#pragma once
#include <starnet/datagram_type.hpp>
#include <inject/udp_request_response.hpp>

#include <string>
#include <stdexcept>

namespace starnet
{
	struct UdpConnectRequest final : inject::UdpRequestResponse
	{
		inline static constexpr size_t maxUsernameSize = 16;
		inline static bool isCorrectUsername(const std::string& username)
		{
			if (username.size() > maxUsernameSize)
				return false;

			for (size_t i = 0; i < username.size(); i++)
			{
				auto value = username[i];

				if (value < 48 || value > 57 && value < 97 && value != 95 || value > 122)
					return false;
			}

			return true;
		}

		inline static constexpr size_t size = headerSize + sizeof(uint8_t) + maxUsernameSize;

		std::string username;

		UdpConnectRequest(const std::string& _username) :
			username(_username)
		{}
		UdpConnectRequest(const std::vector<uint8_t>& buffer, const size_t count)
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
			if (!isCorrectUsername(username))
				throw std::runtime_error("Incorrect username value");

			SDL_WriteU8(context, static_cast<Uint8>(DatagramType::Connect));

			auto usernameSize = username.size();
			SDL_WriteU8(context, static_cast<Uint8>(usernameSize));
			SDL_RWwrite(context, username.data(), sizeof(char), usernameSize);

			if (usernameSize < maxUsernameSize)
			{
				for (size_t i = usernameSize; i < maxUsernameSize; i++)
					SDL_WriteU8(context, 0);
			}
		}
		void fromBytes(SDL_RWops* context) override
		{
			SDL_ReadU8(context);

			auto usernameSize = static_cast<size_t>(SDL_ReadU8(context));

			if(usernameSize > maxUsernameSize)
				throw std::runtime_error("Incorrect username size");

			username = std::string(usernameSize, ' ');
			SDL_RWread(context, username.data(), sizeof(char), usernameSize);

			if (!isCorrectUsername(username))
				throw std::runtime_error("Incorrect username value");

			if (usernameSize < maxUsernameSize)
			{
				for (size_t i = usernameSize; i < maxUsernameSize; i++)
					SDL_ReadU8(context);
			}
		}
	};
}