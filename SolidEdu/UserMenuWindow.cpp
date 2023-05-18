#include "UserMenuWindow.h"
#include "FriendsWindow.h"
#include "InboxWindow.h"
#include "LoginWindow.h"
#include "StudentDecorator.h"
#include "MeetPeopleWindow.h"
#include "AllCoursesWindow.h"
#include "MyCoursesWindow.h"
#include "AcceptFriendRequestsWindow.h"
#include "Factory.h"
#include "WelcomeWindow.h"

// todo . replace with -> for factory
namespace solid_edu
{
	UserMenuWindow::UserMenuWindow(std::unique_ptr<IUser> user) : user{ std::move(user) } {}

	UserMenuWindow::UserMenuWindow(const std::string& username) : user{ Factory::GetSystemApp()->getUser(username)} {}

	std::unique_ptr<IWindow> UserMenuWindow::runThenReturnWindow()
	{
		system("cls");

		std::cout << "1. Inbox: " << user->getInbox()->getNotificationsBadge();
		std::cout << "\n2. Friends\n";
		std::cout << "3. Friend Requests: " << Factory::GetNotifierForFriendRequests(user->getUsername())->getNotificationsBadge();
		std::cout << "\n4. Meet people\n";
		std::cout << "5. My classes\n";
		std::cout << "6. All classes\n";
		std::cout << "7. Logout\n";

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
			return std::unique_ptr<IWindow>{ new InboxWindow(std::unique_ptr<IUser>{user->clone()})};
		case 2:
			return std::unique_ptr<IWindow>{ new FriendsWindow(std::unique_ptr<IUser>{user->clone()})};
		case 3:
			return std::unique_ptr<IWindow>{ new AcceptFriendRequestsWindow(std::unique_ptr<IUser>{user->clone()},
				Factory::GetNotifierForFriendRequests(user->getUsername())->getNotificationsPeers())};
		case 4:
			return std::unique_ptr<IWindow>{ new MeetPeopleWindow(std::unique_ptr<IUser>{user->clone()})};
		case 5:
			return std::unique_ptr<IWindow> {new MyCoursesWindow(std::unique_ptr<IUser>{user->clone()})};
		case 6:
			return std::unique_ptr<IWindow> {new AllCoursesWindow(std::unique_ptr<IUser>{user->clone()})};
		case 7:
		default:
			return std::unique_ptr<IWindow>{ new WelcomeWindow()};
		}
	}
}
