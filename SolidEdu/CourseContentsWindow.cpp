#include "CourseContentsWindow.h"
#include "AcceptCourseApplicationRequestWindow.h"
#include "TeacherGradeWindow.h"
#include "TeacherAddOrRemovePrerequisitesWindow.h"
#include "UserMenuWindow.h"
#include "Factory.h" 

namespace solid_edu
{
	CourseContentsWindow::CourseContentsWindow(const Course& course, std::unique_ptr<IUser> user)
		: course{ course }, user{ std::move(user) } {}

	std::unique_ptr<IWindow> CourseContentsWindow::runThenReturnWindow()
	{
		if (course.hasStudent(user->getUsername()))
		{
			std::cout << "Course: " << course.getCourseTitle() << std::endl;
			std::cout << "\n1. Return to menu" << std::endl;

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
			default:
				return std::unique_ptr<IWindow>{ new UserMenuWindow(std::unique_ptr<IUser>{user->clone()})};
			}
		}
		else if (course.hasTeacher(user->getUsername()))
		{
			std::cout << "Course: " << course.getCourseTitle() << std::endl;
			std::cout << "1. Registration requests: " << Factory::GetNotifierForCourseApplicationRequests(course.getCourseTitle())
				->getNotificationsBadge() << std::endl;
			std::cout << "2. Add/Remove prerequisites" << std::endl;
			std::cout << "3. Grade a student" << std::endl;
			std::cout << "4. Approve a student's course completion" << std::endl;

			std::cout << "\n5. Return to menu" << std::endl;

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
				return std::unique_ptr<IWindow>{
					new AcceptCourseApplicationRequestWindow{
						std::unique_ptr<IUser>{user->clone()},
						course,
						Factory::GetNotifierForCourseApplicationRequests(course.getCourseTitle())
						->getNotificationsPeers()
					}
				};
			case 2:
				return std::unique_ptr<IWindow>{ new TeacherAddOrRemovePrerequisitesWindow(std::unique_ptr<IUser>{user->clone()}, course)};
			case 3:
				return std::unique_ptr<IWindow>{
					new TeacherGradeWindow(std::unique_ptr<IUser>{user->clone()},
						course,
						TeacherGradeWindow::GradeMode::Grade)
				};
			case 4:
				return std::unique_ptr<IWindow>{
					new TeacherGradeWindow(std::unique_ptr<IUser>{user->clone()},
						course,
						TeacherGradeWindow::GradeMode::Completed)
				};
			case 5:
			default:
				return std::unique_ptr<IWindow>{ new UserMenuWindow(std::unique_ptr<IUser>{user->clone()})};
			}
		}
		else
		{
			std::cout << "1. Register" << std::endl;
			std::cout << "\n2. Return to menu" << std::endl;

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
				course.ApplyForRegistration(user->getUsername());
				return std::unique_ptr<IWindow>{ new UserMenuWindow(std::unique_ptr<IUser>{user->clone()})};
			case 2:
			default:
				return std::unique_ptr<IWindow>{ new UserMenuWindow(std::unique_ptr<IUser>{user->clone()})};
			}
		}
	}
}
