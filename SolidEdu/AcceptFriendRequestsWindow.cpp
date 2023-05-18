#include "AcceptFriendRequestsWindow.h"
#include "UserMenuWindow.h"
#include "Factory.h"

namespace solid_edu
{

	AcceptFriendRequestsWindow::AcceptFriendRequestsWindow(std::unique_ptr<IUser> user, const std::vector<std::string>& requests)
		: user{ std::move(user) }, requests{ requests } {}

	std::unique_ptr<IWindow> AcceptFriendRequestsWindow::runThenReturnWindow()
	{
		for (auto request : requests)
		{
			std::cout << request << ":" << '\n';
			std::cout << "1. Accept" << '\n';
			std::cout << "2. Decline" << '\n';

			int option = -1;
			std::cout << "> ";
			std::cin >> option;
			while ((std::cin.fail()))
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Error: Please enter an option's number\n";
				std::cout << "> ";
				std::cin >> option;
			}

			switch (option)
			{
			case 1:
				if (Factory::GetSystemApp()->isUsernameRegistered(request))
				{
					Factory::GetConnectionsManager()->AddFriend(request, user->getUsername());
				}
				else
				{
					std::cout << "The student is not registered anymore" << '\n';
				}
				break;

			default:
				continue;
			}
		}

		return std::unique_ptr<IWindow>{ new UserMenuWindow(std::unique_ptr<IUser>{user->clone()}) };
	};
}
