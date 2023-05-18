#pragma once

#include "AddOrRemove.h"
#include "AdministratorMenuWindow.h"

namespace solid_edu
{
	template<>
	class AddOrRemove<add_remove::Grades>
	{
	public:
		std::unique_ptr<IWindow> add()
		{
			std::string username = readUsername();
			if (!Factory::GetSystemApp()->isUsernameRegistered(username))
			{
				std::cout << "The user is not registered." << '\n';
				system("pause");
				return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
			}

			std::cout << "Enter completed courses and grades [semicolon-separated in form: courseName_passed(true/false)_grade] "
				"\neg. matematika1_true_10;fizika_false_0" << '\n';

			std::string course_passed_grade_List;
			std::getline(std::cin >> std::ws, course_passed_grade_List);
			if (stringlib::endsWith(course_passed_grade_List, ";"))
			{
				course_passed_grade_List.erase(course_passed_grade_List.length() - 1);
			}

			// grades for all users will be all in a single file written as: 
			//		user1:class1_true_9;class2_false_0
			//		user2:class1_true_8;class3_true_10
			Factory::GetCompletedCoursesFileManager()->AddCompletedCourseInfoForUser(course_passed_grade_List, username);

			return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
		}

		std::unique_ptr<IWindow> remove()
		{
			std::string username = readUsername();
			if (!Factory::GetSystemApp()->isUsernameRegistered(username))
			{
				std::cout << "The user is not registered." << '\n';
				system("pause");
				return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
			}

			std::cout << "Enter courses' names [comma-separated]" << '\n';
			std::string courseNames;
			std::getline(std::cin >> std::ws, courseNames);
			auto courses = stringlib::split(courseNames, ',');
			auto p = std::remove_if(courses.begin(), courses.end(),
				[](auto& course)
				{
					return !Factory::GetSystemApp()->isCourseRegistered(course);
				}
			);
			if (p != courses.end())
				courses.erase(p, courses.end());

			for (auto& course : courses)
			{
				Factory::GetCompletedCoursesFileManager()->RemoveSingleCourseFromUsersCompletedCourses(course, username);
			}

			return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
		}

	private:
		std::string readUsername()
		{
			std::cout << "Enter username" << '\n';
			std::string username{};
			std::getline(std::cin >> std::ws, username);
			return username;
		}
	};
}