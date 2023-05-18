#pragma once

#include "AddOrRemove.h"
#include "AdministratorMenuWindow.h"
#include "Course.h"

namespace solid_edu
{
	template<>
	class AddOrRemove<add_remove::CoursesTeachers>
	{
	public:
		std::unique_ptr<IWindow> add()
		{
			std::string courseName = readCourse();
			if (!Factory::GetSystemApp()->isCourseRegistered(courseName))
			{
				std::cout << "The course is not registered." << '\n';
				system("pause");
				return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
			}

			auto teachers = readTeachers();

			Course course{ courseName };
			for (auto& teacher : teachers)
			{
				course.RegisterTeacher(teacher);
			}

			return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
		}

		std::unique_ptr<IWindow> remove()
		{
			std::string courseName = readCourse();
			if (!Factory::GetSystemApp()->isCourseRegistered(courseName))
			{
				std::cout << "The user is not registered." << '\n';
				system("pause");
				return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
			}

			auto teachers = readTeachers();

			Course course{ courseName };
			std::vector<std::string> students{};

			for (auto& student : course.GetStudents())
			{
				students.push_back(student);
			}

			for (auto& teacher : teachers)
			{
				Factory::GetUser(teacher)->getInbox()->removeConversations(students);
				course.RemoveTeacher(teacher);
			}

			return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
		}

	private:
		std::string readCourse()
		{
			std::cout << "Enter course's name:\n>";

			std::string course{};
			std::getline(std::cin >> std::ws, course);
			return course;
		}

		std::vector<std::string> readTeachers()
		{
			std::cout << "Enter teachers [comma-separated]" << '\n';
			std::string teachersString{};
			std::getline(std::cin >> std::ws, teachersString);
			auto teachers = stringlib::split(teachersString, ',');
			auto p = std::remove_if(teachers.begin(), teachers.end(),
				[](auto& course)
				{
					return !Factory::GetSystemApp()->isUsernameRegistered(course);
				}
			);
			if (p != teachers.end())
				teachers.erase(p, teachers.end());
			return teachers;
		}
	};
}