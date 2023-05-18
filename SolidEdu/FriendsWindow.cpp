#include "FriendsWindow.h"
#include "ConversationWindow.h"
#include "UserMenuWindow.h"
#include  "Factory.h"
#include "FilterMessagesWindow.h"

namespace solid_edu
{

	FriendsWindow::FriendsWindow(std::unique_ptr<IUser> user)
		: user{ std::move(user) } {}

	std::unique_ptr<IWindow> FriendsWindow::runThenReturnWindow()
	{
		auto friendList = Factory::GetConnectionsManager()->GetFriends(user->getUsername());
		int counter = 0;
		for (auto aFriend : friendList)
		{
			counter++;
			std::cout << counter << ". " << aFriend << '\n';
		}
		int limes = counter;
		std::vector<std::string> teacherList;
		for (auto& course : user->getCourses())
		{
			for (auto& teacher : course.GetTeachers())
			{
				if (teacher == user->getUsername())
				{
					continue;
				}

				counter++;
				std::cout << counter << ". " << course << " teacher: " << teacher << '\n';

				teacherList.push_back(teacher);
			}
		}

		std::cout << (counter + 1) << ". Filter messages:" << '\n';
		std::cout << "\n" << (counter + 2) << ". Return to menu" << '\n';

		int option = -1;
		std::cout << "> ";
		std::cin >> option;
		while (std::cin.fail() || option > counter + 2 || option <= 0)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Error: Please enter an option's number\n";
			std::cout << "> ";
			std::cin >> option;
		}

		if (option == counter + 1)
		{
			return std::unique_ptr<IWindow>{
				new FilterMessagesWindow(std::unique_ptr<IUser>{user->clone()})
			};
		}
		if (option == counter + 2)
		{
			return std::unique_ptr<IWindow>{new UserMenuWindow(std::unique_ptr<IUser>{user->clone()})};
		}
		if (option <= limes)
		{
			return std::unique_ptr<IWindow>{new ConversationWindow(friendList[option - 1],
				std::unique_ptr<IUser>{user->clone()})};
		}
		else
		{
			return std::unique_ptr<IWindow>{new ConversationWindow(teacherList[option - (limes + 1)], std::unique_ptr<IUser>{user->clone()})};
		}
	}
}
