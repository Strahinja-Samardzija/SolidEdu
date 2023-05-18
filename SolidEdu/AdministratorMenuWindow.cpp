#include "AdministratorMenuWindow.h"
#include "GenericAddOrRemove.h"
#include "UserAddOrRemove.h"
#include "UsersFriendsAddOrRemoveAdministratorWindow.h"
#include "UsersFriendsAddOrRemoveAdministratorWindow.h"
#include "CourseAddOrRemoveAdministrator.h"
#include "CoursesPrerequisitesAddOrRemoveAdministrator.h"
#include "CoursesStudentsAddOrRemoveAdministrator.h"
#include "CoursesTeachersAddOrRemoveAdministrator.h"
#include "DepartmentAddOrRemoveAdministrator.h"
#include "DepartmentsCoursesAddOrRemoveAdministrator.h"
#include "GradesAddOrRemoveAdministrator.h"
#include "LoginWindow.h"
#include "WelcomeWindow.h"

namespace solid_edu
{
	std::unique_ptr<IWindow> AdministratorMenuWindow::runThenReturnWindow()
	{
		system("cls");

		std::cout << "1. Add/Remove a user " << '\n';
		std::cout << "2. Add/Remove a course " << '\n';
		std::cout << "3. Add/Remove a user's friends " << '\n';
		std::cout << "4. Add/Remove a course's students " << '\n';
		std::cout << "5. Add/Remove a course's teachers " << '\n';
		std::cout << "6. Add/Remove a course's prerequisites " << '\n';
		std::cout << "7. Add/Remove a user's completed courses and grades " << '\n';
		std::cout << "8. Add/Remove a department " << '\n';
		std::cout << "9. Add/Remove a department's courses " << '\n';
		std::cout << "10. Logout " << '\n';

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
			return std::unique_ptr<IWindow>{ new GenericAddOrRemove<add_remove::User> };
		case 2:
			return std::unique_ptr<IWindow>{new GenericAddOrRemove<add_remove::Course> };
		case 3:
			return std::unique_ptr<IWindow>{new GenericAddOrRemove<add_remove::UsersFriends> };
		case 4:
			return std::unique_ptr<IWindow>{new GenericAddOrRemove<add_remove::CoursesStudents> };
		case 5:
			return std::unique_ptr<IWindow>{new GenericAddOrRemove<add_remove::CoursesTeachers> };
		case 6:
			return std::unique_ptr<IWindow>{new GenericAddOrRemove<add_remove::CoursesPrerequisites> };
		case 7:
			return std::unique_ptr<IWindow>{new GenericAddOrRemove<add_remove::Grades> };
		case 8:
			return std::unique_ptr<IWindow>{new GenericAddOrRemove<add_remove::Department> };
		case 9:
			return std::unique_ptr<IWindow>{new GenericAddOrRemove<add_remove::DepartmentsCourses> };
		case 10:
		default:
			return std::unique_ptr<IWindow>{new WelcomeWindow()};
		}
	}
}
