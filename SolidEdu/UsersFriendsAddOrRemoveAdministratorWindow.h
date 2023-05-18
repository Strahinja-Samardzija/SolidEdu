#pragma once

#include "AddOrRemove.h"
#include "AdministratorMenuWindow.h"

namespace solid_edu
{
	template<>
	class AddOrRemove<add_remove::UsersFriends>
	{
	public:
		std::unique_ptr<IWindow> add()
		{
			std::string user = readUser();
			if (!Factory::GetSystemApp()->isUsernameRegistered(user))
			{
				std::cout << "The user is not registered." << '\n';
				system("pause");
				return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
			}

			auto friends = readFriends(user);
			for (const auto& aFriend : friends)
			{
				Factory::GetConnectionsManager()->AddFriend(user, aFriend);
			}

			return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
		}

		std::unique_ptr<IWindow> remove()
		{
			std::string user = readUser();
			if (!Factory::GetSystemApp()->isUsernameRegistered(user))
			{
				std::cout << "The user is not registered." << '\n';
				system("pause");
				return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
			}

			auto friends = readFriends(user);

			for (const auto& aFriend : friends)
			{
				Factory::GetUser(user)->getInbox()->removeConversations(std::vector<std::string>{aFriend});
				Factory::GetConnectionsManager()->RemoveFriend(user, aFriend);
			}

			return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
		}

	private:
		std::string readUser()
		{
			std::cout << "Enter user's name:\n>";

			std::string username{};
			std::getline(std::cin >> std::ws, username);
			return username;
		}

		std::vector<std::string> readFriends(const std::string& username)
		{
			std::cout << "Enter friends [comma-separated]" << '\n';
			std::string friendsString{};
			std::getline(std::cin >> std::ws, friendsString);
			auto friends = stringlib::split(friendsString, ',');
			auto p = std::remove_if(friends.begin(), friends.end(),
				[](auto& aFriend)
				{
					return !Factory::GetSystemApp()->isUsernameRegistered(aFriend);
				}
			);
			if (p != friends.end())
				friends.erase(p, friends.end());
			return friends;
		}
	};
}