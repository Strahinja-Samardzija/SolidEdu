#pragma once

#include "Departments.h"
#include "AddOrRemove.h"
#include "AdministratorMenuWindow.h"

namespace solid_edu
{
	template<>
	class AddOrRemove<add_remove::Department>
	{
	public:
		std::unique_ptr<IWindow> add()
		{
			std::string departmentName = readDepartment();
			if (Departments::isDepartmentRegistered(departmentName))
			{
				std::cout << "The department is already registered." << '\n';
				system("pause");
				return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
			}

			auto courses = readCourses();
			Departments::RegisterDepartment(departmentName, courses);

			return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
		}

		std::unique_ptr<IWindow> remove()
		{
			std::string departmentName = readDepartment();
			if (Departments::isDepartmentRegistered(departmentName))
			{
				std::cout << "The department is not registered." << '\n';
				system("pause");
				return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
			}

			Departments::removeDepartment(departmentName);

			return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
		}

	private:
		std::string readDepartment()
		{
			std::cout << "Enter department's name:\n>";

			std::string department{};
			std::getline(std::cin >> std::ws, department);
			return department;
		}

		std::vector<std::string> readCourses()
		{
			std::cout << "Note: a department might be added after all it's courses are registered."
				"\nYou can register new courses later and then add them "
				"to a department, but now only enter courses that are already registered or enter 'none'.\n";
			std::cout << "Enter courses that are already registered [comma-separated]\n>";
			std::string coursesString{};
			std::getline(std::cin >> std::ws, coursesString);
			auto courses = stringlib::split(coursesString, ',');
			auto p = std::remove_if(courses.begin(), courses.end(),
				[](auto& course)
				{
					return !Factory::GetSystemApp()->isCourseRegistered(course);
				}
			);
			if (p != courses.end())
				courses.erase(p, courses.end());
			return courses;
		}
	};
}
