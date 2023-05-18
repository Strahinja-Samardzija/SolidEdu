#pragma once

#include "IWindow.h"
#include "IUser.h"
#include "Course.h"

namespace add_remove
{
	class InterfaceAddRemove {};
	class User : public InterfaceAddRemove {};
	class UsersFriends : public InterfaceAddRemove{};
	
	class Course : public InterfaceAddRemove {};
	class CoursesTeachers : public InterfaceAddRemove {};
	class CoursesStudents : public InterfaceAddRemove {};
	class CoursesPrerequisites : public InterfaceAddRemove {};
	class Grades : public InterfaceAddRemove {};

	class Department : public InterfaceAddRemove {};
	class DepartmentsCourses : public InterfaceAddRemove {};
}

namespace solid_edu
{/*
 */
	template<class T>
	concept DerivedInterfaceFromAddRemove = std::is_base_of<add_remove::InterfaceAddRemove, T>::value;

	template<DerivedInterfaceFromAddRemove>
	class AddOrRemove
	{
	public:
		std::unique_ptr<IWindow> add() = 0;
		std::unique_ptr<IWindow> remove() = 0;
	};

	template<>
	class AddOrRemove<add_remove::User>;
	template<>
	class AddOrRemove<add_remove::UsersFriends>;

	template<>
	class AddOrRemove<add_remove::Course>;
	template<>
	class AddOrRemove<add_remove::CoursesTeachers>;
	template<>
	class AddOrRemove<add_remove::CoursesStudents>;
	template<>
	class AddOrRemove<add_remove::CoursesPrerequisites>;
	template<>
	class AddOrRemove<add_remove::Grades>;

	template<>
	class AddOrRemove<add_remove::Department>;
	template<>
	class AddOrRemove<add_remove::DepartmentsCourses>;
}