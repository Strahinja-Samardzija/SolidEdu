#include "ConversationWindow.h"
#include "FriendsWindow.h"
#include "Factory.h"	

namespace solid_edu
{
	ConversationWindow::ConversationWindow(const std::string& aFriend, std::unique_ptr<IUser> user)
		: aFriend{ aFriend },
		user{ std::move(user) },
		conversation{},
		messageReader{}
	{
		conversation = this->user->getInbox()->getConversation(aFriend); 
		messageReader = Factory::GetMessageReader(this->user->getInbox()->getConversation(aFriend));
	}

	std::unique_ptr<IWindow> ConversationWindow::runThenReturnWindow()
	{
		system("cls");

		messageReader->readMessages();
		int option{-1};

		while (option != 3)
		{
			std::cout << "1. New message" << '\n';
			std::cout << "2. Older messages" << '\n';
			std::cout << "\n3. Return" << '\n';

			std::cout << "> ";
			std::cin >> option;
			while ((std::cin.fail()))
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Error: Please enter an option's number\n";
				std::cout << "> ";
			}

			switch (option)
			{
			case 1:
				if (Factory::GetSystemApp()->isUsernameRegistered(aFriend))
				{
					std::string newMessage;
					std::getline(std::cin >> std::ws, newMessage);
					conversation->writeMessage(user->getUsername(), newMessage);
				}
				else
				{
					std::cout << "The user is not registered anymore." << '\n';
					system("pause");
				}
				break;
			case 2:
				messageReader->moreMessages();
				break;
			default:
				break;
			}
		}

		return std::unique_ptr<IWindow>{new FriendsWindow(std::move(user))};
	}
}

