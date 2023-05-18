#pragma once

#include "IConnectionsManager.h"
#include <string>
#include <vector>
#include <stdexcept>
#include "stringlib.h"

namespace solid_edu
{
	class ConnectionsManager : public IConnectionsManager
	{
	public:
		void RegisterUser(const std::string& user) override;

		void RemoveUser(const std::string& user) override;

		void AddFriend(const std::string& user1, const std::string& user2) override;

		void RemoveFriend(const std::string& user1, const std::string& user2) override;

		std::vector<std::string> GetFriends(const std::string& owner) const override;

	private:
		std::string InsertFriendInLine(const std::string& friend_Keyword, std::string& line);

		std::string DeleteFriendFromLine(const std::string& friend_Keyword, std::string& line);
	};
}
