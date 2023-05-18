#pragma once

#include "AddOrRemove.h"
#include "AdministratorMenuWindow.h"
#include "Course.h"

namespace solid_edu
{
	template<>
	class AddOrRemove<add_remove::CoursesStudents>
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

			auto students = readStudents();

			Course course{ courseName };
			for (auto& student : students)
			{
				course.RegisterStudent(student);
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

			auto students = readStudents();

			Course course{ courseName };
			std::vector<std::string> teachers{};
			for (auto& t : course.GetStudents())
			{
				teachers.push_back(t);
			}

			for (auto& student : students)
			{
				try
				{
					Factory::GetUser(student)->getInbox()->removeConversations(teachers);
				}
				catch (const std::exception& e)
				{
					std::cerr << e.what();
					throw std::runtime_error("Could not delete " + student + "'s conversations.");
				}
				course.RemoveStudent(student);
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

		std::vector<std::string> readStudents()
		{
			std::cout << "Enter students [comma-separated]" << '\n';
			std::string studentsString{};
			std::getline(std::cin >> std::ws, studentsString);
			auto students = stringlib::split(studentsString, ',');
			auto p = std::remove_if(students.begin(), students.end(),
				[](auto& course)
				{
					return !Factory::GetSystemApp()->isUsernameRegistered(course);
				}
			);
			if (p != students.end())
				students.erase(p, students.end());
			return students;
		}
	};
}