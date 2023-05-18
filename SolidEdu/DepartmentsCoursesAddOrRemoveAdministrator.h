#pragma once

#include "GenericAddOrRemove.h"
#include "Departments.h"
#include "AddOrRemove.h"
#include "AdministratorMenuWindow.h"

namespace solid_edu
{
	template<>
	class AddOrRemove<add_remove::DepartmentsCourses>
	{
	public:
		std::unique_ptr<IWindow> add()
		{
			std::string departmentName = readDepartment();
			if (!Departments::isDepartmentRegistered(departmentName))
			{
				std::cout << "The department is not registered." << '\n';
				system("pause");
				return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
			}

			auto courses = readCourses();

			for (auto& course : courses)
			{
				Departments::AddCourseToDepartment(course, departmentName);
			}

			return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
		}

		std::unique_ptr<IWindow> remove()
		{

			std::string departmentName = readDepartment();
			if (!Departments::isDepartmentRegistered(departmentName))
			{
				std::cout << "The department is not registered." << '\n';
				system("pause");
				return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
			}

			auto courses = readCourses();

			for (auto& course : courses)
			{
				Departments::RemoveCourseFromDepartment(course, departmentName);
			}

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
			std::cout << "Enter courses [comma-separated] (or enter 'none')" << '\n';
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