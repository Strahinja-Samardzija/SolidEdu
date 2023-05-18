#include "AllCoursesWindow.h"
#include "CourseContentsWindow.h"
#include "Factory.h"

namespace solid_edu
{
	AllCoursesWindow::AllCoursesWindow(std::unique_ptr<IUser> user)
		: user{ std::move(user) } {}

	std::unique_ptr<IWindow> AllCoursesWindow::runThenReturnWindow()
	{
		auto courseSet = Factory::GetSystemApp()->GetCourses();
		std::vector<Course> coursesVector{};
		std::copy(courseSet.cbegin(), courseSet.cend(), std::back_inserter(coursesVector));
		
		int counter = 1;
		for (auto courseName : coursesVector)
		{
			std::cout << "" << counter++ << ". " << courseName << std::endl;
		}

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

		Course courseToView{ coursesVector[option - 1] };
		return std::unique_ptr<IWindow>{ new CourseContentsWindow(courseToView, std::unique_ptr<IUser>{user->clone()}) };
	}
}
