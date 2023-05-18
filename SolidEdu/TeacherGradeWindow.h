#pragma once

#include "IWindow.h"
#include "IUser.h"
#include "Course.h"
#include <string>
#include <vector>
#include <iostream>

namespace solid_edu
{
	class TeacherGradeWindow : public IWindow
	{
	public:
		enum class GradeMode {Grade, Completed};

	private:
		std::unique_ptr<IUser> teacher;
		Course course;
		GradeMode mode;

	public:
		TeacherGradeWindow(std::unique_ptr<IUser> teacher, const Course& course, GradeMode mode);

		std::unique_ptr<IWindow> runThenReturnWindow() override;

	private:
		void approveCompletionForStudent(const std::string& student);

		void gradeStudent(const std::string& student);
	};
}

