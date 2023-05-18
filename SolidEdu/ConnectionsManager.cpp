#include "ConnectionsManager.h"
#include "Factory.h"
#include <regex>

namespace solid_edu
{
	void ConnectionsManager::RegisterUser(const std::string& user)
	{
		stringlib::appendAllLines(Factory::GetSystemPathsDefault()->graphFileDestination, std::vector<std::string> { user + " - " });
	}

	void ConnectionsManager::RemoveUser(const std::string& user)
	{
		auto lines = stringlib::readAllLines(Factory::GetSystemPathsDefault()->graphFileDestination);

		auto p = std::remove_if(lines.begin(), lines.end(),
			[&user](auto& line)
			{
				return stringlib::startsWith(line, user);
			}
		);
		if (p != lines.end())
			lines.erase(p, lines.end());

		std::regex userRegex{ R"(\b)" + user + R"(\b)" };
		for (int i = 0; i < lines.size(); i++)
		{
			if (std::regex_search(lines[i], userRegex))
			{
				lines[i] = DeleteFriendFromLine(user, lines[i]);
			}
		}

		stringlib::writeAllLines(Factory::GetSystemPathsDefault()->graphFileDestination, lines);
	}

	void ConnectionsManager::AddFriend(const std::string& user1, const std::string& user2)
	{
		try
		{
			std::vector<std::string> lines = stringlib::readAllLines(Factory::GetSystemPathsDefault()->graphFileDestination);

			for (int i = 0; i < lines.size(); i++)
			{
				if (stringlib::startsWith(lines[i], user1 + " -"))
				{
					lines[i] = InsertFriendInLine(user2, lines[i]);
				}

				if (stringlib::startsWith(lines[i], user2 + " -"))
				{
					lines[i] = InsertFriendInLine(user1, lines[i]);
				}
			}

			stringlib::writeAllLines(Factory::GetSystemPathsDefault()->graphFileDestination, lines);
		}
		catch (const std::runtime_error& e1)
		{
			throw;
		}
	}

	void ConnectionsManager::RemoveFriend(const std::string& user1, const std::string& user2)
	{
		std::vector<std::string> lines = stringlib::readAllLines(Factory::GetSystemPathsDefault()->graphFileDestination);

		std::regex user1Regex{ R"(\b)" + user1 + R"(\b)" };
		std::regex user2Regex{ R"(\b)" + user2 + R"(\b)" };

		for (auto i = 0; i < lines.size(); i++)
		{
			if (stringlib::startsWith(lines[i], user1 + " -") && std::regex_search(lines[i], user2Regex))
			{
				lines[i] = DeleteFriendFromLine(user2, lines[i]);
			}

			if (stringlib::startsWith(lines[i], user2 + " -") && std::regex_search(lines[i], user1Regex))
			{
				lines[i] = DeleteFriendFromLine(user1, lines[i]);
			}
		}

		stringlib::writeAllLines(Factory::GetSystemPathsDefault()->graphFileDestination, lines);
	}

	std::string ConnectionsManager::InsertFriendInLine(const std::string& aFriend, std::string& line)
	{
		if (stringlib::endsWith(line, "-"))
		{
			line += " " + aFriend;
		}
		else
		{
			line += ", " + aFriend;
		}

		return line;
	}

	std::string ConnectionsManager::DeleteFriendFromLine(const std::string& aFriend, std::string& line)
	{
		std::regex friendRegex{ R"(\b)" + aFriend + R"((,|\b))"};
		line = std::regex_replace(line, friendRegex, "");
		return line;
	}

	std::vector<std::string> ConnectionsManager::GetFriends(const std::string& owner) const
	{
		std::vector<std::string> friends{};

		std::vector<std::string> lines =
			stringlib::readAllLines(Factory::GetSystemPathsDefault()->graphFileDestination);

		for (int i = 0; i < lines.size(); i++)
		{
			if (stringlib::startsWith(lines[i], owner + " -"))
			{
				if (stringlib::endsWith(lines[i], "- "))
				{
					return std::vector<std::string>();
				}

				std::vector<std::string> friendsRead =
					stringlib::split(lines[i].substr(lines[i].find("-") + 1), ',');
				for (auto& name : friendsRead)
				{
					friends.push_back(name);
				}
				break;
			}
		}

		return friends;
	}
}
