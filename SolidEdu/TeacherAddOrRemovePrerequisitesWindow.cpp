#include "TeacherAddOrRemovePrerequisitesWindow.h"
#include "CourseContentsWindow.h"
#include "CoursePrerequisiteModifier.h"

namespace solid_edu
{
	TeacherAddOrRemovePrerequisitesWindow::TeacherAddOrRemovePrerequisitesWindow(std::unique_ptr<IUser> user, const Course& course)
		: user{ std::move(user) }, course{ course } {}

	std::unique_ptr<IWindow> TeacherAddOrRemovePrerequisitesWindow::runThenReturnWindow()
	{
		std::cout << "1. Add a prerequisite:" << '\n';
		std::cout << "2. Remove a prerequisite:" << '\n';

		std::cout << "\n3. Return to course contents" << '\n';

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

		CoursePrerequisiteModifier modifierForCourse{course};
		switch (option)
		{
		case 1:
			modifierForCourse.AddPrerequisite();
			return std::unique_ptr<IWindow>{ new CourseContentsWindow(course, std::unique_ptr<IUser>{user->clone()}) };
		case 2:
			modifierForCourse.RemovePrerequisite();
			return std::unique_ptr<IWindow>{ new CourseContentsWindow(course, std::unique_ptr<IUser>{user->clone()}) };
		case 3:
		default:
			return std::unique_ptr<IWindow>{ new CourseContentsWindow(course, std::unique_ptr<IUser>{user->clone()}) };
		}
	}
}
