#include <iostream>
#include <memory>
#include "ConnectionsGraphLib.h"
#include "IWindow.h"
#include "PrerequisiteTypes.h" 
#include "WelcomeWindow.h"
#include "Factory.h"
#include <regex>

using namespace solid_edu;

int main()
{
	Factory::GetSystemApp();
	PrerequisiteTypes::InitializeTypes();

	std::unique_ptr<IWindow> welcomeWindow{ new WelcomeWindow() };

	std::unique_ptr<IWindow> nextWindow{ welcomeWindow->runThenReturnWindow() };

	// ExitWindow will return null
	while (nextWindow != nullptr)
	{
		try
		{
			nextWindow = nextWindow->runThenReturnWindow();
		}
		catch (std::exception)
		{
			std::cout << ("System's data is corrupt. Ask a system administrator for help.\n");
			system("pause");
			return 1;
		}
	}
	return 0;
}

