#include "InboxWindow.h"
#include "UserMenuWindow.h"
#include "AnswerWindow.h"

namespace solid_edu
{

	InboxWindow::InboxWindow(std::unique_ptr<IUser> user)
		: user{ std::move(user) } {}

	std::unique_ptr<IWindow> InboxWindow::runThenReturnWindow()
	{
		auto peers = user->getInbox()->getNotificationsPeers();
		int counter = 0;

		std::cout << "New messages from: " << '\n';
		for (auto& peer : peers)
		{
			counter++;
			std::cout << peer << '\n';
		}

		std::cout << "\n1. Answer" << '\n';
		std::cout << "\n\n2. Return to menu" << '\n';

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
			return std::unique_ptr<IWindow>{new AnswerWindow(peers, std::unique_ptr<IUser>{user->clone()})};
		default:
			break;
		}

		return std::unique_ptr<IWindow>{new UserMenuWindow(std::unique_ptr<IUser>{user->clone()})};
	}
}
 