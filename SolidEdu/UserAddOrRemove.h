#pragma once

#include "Factory.h"
#include "AddOrRemove.h"
#include "AdministratorMenuWindow.h"

namespace solid_edu
{
	template<>
	class AddOrRemove<add_remove::User>
	{
	public:
		std::unique_ptr<IWindow> add()
		{
			std::string username = getUsername();
			if (Factory::GetSystemApp()->isUsernameRegistered(username))
			{
				std::cout << "The user is already registered." << '\n';
				system("pause");
				return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
			}

			std::string password = getPassword();

			Factory::GetSystemApp()->RegisterUser(username, password);
			return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
		}

		std::unique_ptr<IWindow> remove()
		{
			std::string username = getUsername();
			if (!Factory::GetSystemApp()->isUsernameRegistered(username))
			{
				std::cout << "The user is not registered." << '\n';
				system("pause");
				return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
			}

			try
			{
				Factory::GetSystemApp()->RemoveUser(username);
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what();
			}
			return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
		}

	private:
		std::string getUsername()
		{
			std::cout << "Enter user's data:\n";
			std::cout << "username:\n>";

			std::string username{};
			std::getline(std::cin >> std::ws, username);
			return username;
		}

		std::string getPassword()
		{
			std::cout << "password:\n>";
			std::string pw{};
			std::getline(std::cin >> std::ws, pw);
			return pw;
		}
	};
}
