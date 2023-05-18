#pragma once

#include "IWindow.h"
#include "IUser.h"
#include "AdministratorMenuWindow.h"
#include "AddOrRemove.h"

namespace solid_edu
{
	template<typename T>
	class GenericAddOrRemove : public IWindow
	{
	public:
		std::unique_ptr<IWindow> runThenReturnWindow() override
		{
			std::cout << "1. Add" << '\n';
			std::cout << "2. Remove" << '\n';
			std::cout << "3. Return" << '\n';

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

			AddOrRemove<T> addOrRemoveObj{};
			switch (option)
			{
			case 1:
				return addOrRemoveObj.add();
			case 2:
				return addOrRemoveObj.remove();
			case 3:
			default:
				return std::unique_ptr<IWindow> {new AdministratorMenuWindow()};
			}
		}
	};
}
