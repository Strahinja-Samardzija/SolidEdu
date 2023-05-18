#include "FilterMessagesWindow.h"
#include "Conversation.h"
#include "FilterMessageReader.h"
#include "FriendsWindow.h"

namespace solid_edu
{
	FilterMessagesWindow::FilterMessagesWindow(std::unique_ptr<IUser> user)
		: user{ std::move(user) } {}

	std::unique_ptr<IWindow> solid_edu::FilterMessagesWindow::runThenReturnWindow()
	{
		system("cls");

		std::cout << "Filter string:\n";
		std::cout << "> ";
		std::string filter;
		std::getline(std::cin >> std::ws, filter);

		FilterMessageReader reader{ user->getUsername(), filter };

		reader.readMessages();

		while (true)
		{
			std::cout << "1. More" << '\n';
			std::cout << "\n2. Return" << '\n';

			std::cout << "> ";

			int option{ -1 };
			std::cin >> option;
			while ((std::cin.fail()) || option < 1 || option > 2)
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Error: Please enter an option's number\n";
				std::cout << "> ";
			}

			switch (option)
			{
			case 1:
				reader.moreMessages();
				break;
			case 2:
			default:
				return std::unique_ptr<IWindow>{new FriendsWindow(std::move(user))};
			}
		}
	}
}
