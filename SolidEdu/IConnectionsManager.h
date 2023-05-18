#pragma once

#include <string>
#include <vector>

namespace solid_edu
{
	class IConnectionsManager
	{
	public:
		virtual void AddFriend(const std::string& user1, const std::string& user2) = 0;
		virtual std::vector<std::string> GetFriends(const std::string& owner) const  = 0;
		virtual void RegisterUser(const std::string& user) = 0;
		virtual void RemoveFriend(const std::string& user1, const std::string& user2) = 0;
		virtual void RemoveUser(const std::string& user) = 0;

		virtual ~IConnectionsManager() = 0 {};
	};
}
