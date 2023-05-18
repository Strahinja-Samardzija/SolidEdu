#include "AcceptCourseApplicationRequestWindow.h"
#include "CourseContentsWindow.h"
#include "Factory.h"

namespace solid_edu
{
	AcceptCourseApplicationRequestWindow::AcceptCourseApplicationRequestWindow(
		std::unique_ptr<IUser> user,
		const Course& course,
		const std::vector<std::string>& requestSenders
	)
		: user{ std::move(user) }, course{ course }, requestSenders{ requestSenders } {}

	std::unique_ptr<IWindow> AcceptCourseApplicationRequestWindow::runThenReturnWindow()
	{
		for (auto& request : requestSenders)
		{
			std::cout << request << ":" << '\n';
			std::cout << "1. Accept" << '\n';
			std::cout << "2. Decline" << '\n';

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
				if (Factory::GetSystemApp()->isUsernameRegistered(request))
				{
					course.RegisterStudent(request);
				}
				else
				{
					std::cout << "The student is not registered anymore" << '\n';
				}
				break;
			default:
				continue;
			}
		}

		return std::unique_ptr<IWindow>{ new CourseContentsWindow(course, std::unique_ptr<IUser>{user->clone()}) };
	}
}
