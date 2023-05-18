#pragma once

#include "AddOrRemove.h"
#include "AdministratorMenuWindow.h"

namespace solid_edu
{
	template<>
	class AddOrRemove<add_remove::Course>
	{
	public:
		std::unique_ptr<IWindow> add()
		{
			std::string courseName = getCourseName();
			if (Factory::GetSystemApp()->isCourseRegistered(courseName))
			{
				std::cout << "The course is already registered." << '\n';
				system("pause");
				return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
			}

			Factory::GetSystemApp()->RegisterCourse(courseName);
			return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
		}

		std::unique_ptr<IWindow> remove()
		{
			std::string courseName = getCourseName();
			if (!Factory::GetSystemApp()->isCourseRegistered(courseName))
			{
				std::cout << "The course is not registered." << '\n';
				system("pause");
				return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
			}

			Factory::GetSystemApp()->RemoveCourse(courseName);
			return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
		}

	private:
		std::string getCourseName()
		{
			std::cout << "Enter course's name:\n>";

			std::string courseName{};
			std::getline(std::cin >> std::ws, courseName);
			return courseName;
		}
	};
}
