#pragma once

#include "CoursePrerequisiteModifier.h"
#include "AddOrRemove.h"
#include "AdministratorMenuWindow.h"
#include "Course.h"

namespace solid_edu
{
	template<>
	class AddOrRemove<add_remove::CoursesPrerequisites>
	{
	public:
		std::unique_ptr<IWindow> add()
		{
			auto course = readCourse();
			if (course == nullptr)
			{
				return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
			}

			CoursePrerequisiteModifier temp{ *course };
			temp.AddPrerequisite();

			return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
		}

		std::unique_ptr<IWindow> remove()
		{
			auto course = readCourse();
			if (course == nullptr)
			{
				return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
			}

			CoursePrerequisiteModifier temp{ *course };
			temp.RemovePrerequisite();

			return std::unique_ptr<IWindow>{ new AdministratorMenuWindow() };
		}

	private:
		std::unique_ptr<Course> readCourse()
		{
			std::cout << "Enter course's name" << '\n';
			std::string course;
			std::getline(std::cin >> std::ws, course);
			if (Factory::GetSystemApp()->isCourseRegistered(course))
			{
				return std::unique_ptr<Course> {new Course{ course }};
			}
			else
			{
				std::cout << "The course is not registered." << '\n';
				system("pause");
				return nullptr;
			}
		}
	};
}