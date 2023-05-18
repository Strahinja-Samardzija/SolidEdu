#include "WelcomeWindow.h"
#include "LoginWindow.h"
#include "StatsWindow.h"

namespace solid_edu
{
	std::unique_ptr<IWindow> WelcomeWindow::runThenReturnWindow()
	{
		system("cls");

		std::cout << "1. Login\n";
		std::cout << "2. System Stats (Course Comparison, Connections Graph)\n";

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
			return std::unique_ptr<IWindow>{ new LoginWindow{}};
		case 2:
			return std::unique_ptr<IWindow>{ new StatsWindow{}};
		default:
			return std::unique_ptr<IWindow>{ new WelcomeWindow{}};
		}
	}
}
