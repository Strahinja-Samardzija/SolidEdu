#include "LoginWindow.h"
#include "ExitWindow.h"
#include "UserMenuWindow.h"
#include "AdministratorMenuWindow.h"
#include "Factory.h"

namespace solid_edu
{
	int LoginWindow::triesCount = 0;

	std::unique_ptr<IWindow> LoginWindow::runThenReturnWindow()
	{
		if (triesCount == 0)
		{
			system("cls");
		}
		std::cout << "username: [type shutdown to exit]\n";
		std::string username;
		std::getline(std::cin >> std::ws, username);
		if (username == "shutdown")
		{
			return std::unique_ptr<IWindow>{new ExitWindow()};
		}

		std::cout << "password: [type shutdown to exit]\n";
		std::string password;
		std::getline(std::cin >> std::ws, password);
		if (password == "shutdown")
		{
			return std::unique_ptr<IWindow>{new ExitWindow()};
		}

		if (username == "admin" && password == "admin")
		{
			triesCount = 0;
			return std::unique_ptr<IWindow>{new AdministratorMenuWindow()};
		}
		else if (Factory::GetSystemApp()->CheckPassword(username, password))
		{
			triesCount = 0;
			return std::unique_ptr<IWindow> {new UserMenuWindow(username)};
		}
		else
		{
			if (triesCount < 3)
			{
				triesCount++;
				std::cout << "Incorrect username or password.\n";
				return std::unique_ptr<IWindow>{new LoginWindow()};
			}
			else
			{
				triesCount = 0;
				return std::unique_ptr<IWindow>{new ExitWindow()};
			}
		}
	}
}
