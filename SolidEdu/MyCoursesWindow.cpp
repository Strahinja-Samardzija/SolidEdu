#include "MyCoursesWindow.h"
#include "UserMenuWindow.h"
#include "CourseContentsWindow.h"

namespace solid_edu
{
	MyCoursesWindow::MyCoursesWindow(std::unique_ptr<IUser> user)
		: user{ std::move(user) } {}

	std::unique_ptr<IWindow> MyCoursesWindow::runThenReturnWindow()
	{
		auto courseSet = user->getCourses();
		std::vector<Course> coursesVector{};
		std::copy(courseSet.cbegin(), courseSet.cend(), std::back_inserter(coursesVector));

		int counter = 0;
		for (auto& course : coursesVector)
		{
			counter++;
			std::cout << "" << counter << ". " << course.getCourseTitle() << std::endl;
		}

		std::cout << "\n" << (counter + 1) << ". " << "Return to menu" << std::endl;

		int option = -1;
		std::cout << "> ";
		std::cin >> option;
		while ((std::cin.fail()) || option > counter + 1 || option <= 0)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Error: Please enter an option's number\n";
			std::cout << "> ";
			std::cin >> option;
		}

		if (option == counter + 1)
		{
			return std::unique_ptr<IWindow>{ new UserMenuWindow(std::unique_ptr<IUser>{user->clone()}) };
		}
		else
		{
			CourseContentsWindow temp{ coursesVector[option - 1], std::unique_ptr<IUser>{user->clone()} };
			return temp.runThenReturnWindow();
		}
	}
}
