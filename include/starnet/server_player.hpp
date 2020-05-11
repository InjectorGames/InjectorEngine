#pragma once
#include <string>

namespace starnet
{
	class ServerPlayer
	{
	protected:
		uint64_t id;
		std::string username;
	public:
		ServerPlayer(const uint64_t _id, const std::string& _username) :
			id(_id),
			username(_username)
		{}

		inline uint64_t getId() const
		{
			return id;
		}
		inline const std::string& getUsername() const
		{
			return username;
		}
	};
}
