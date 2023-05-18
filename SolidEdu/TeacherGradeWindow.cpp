#include "TeacherGradeWindow.h"
#include "CourseContentsWindow.h"
#include "Factory.h"

#include <algorithm>
#include <sstream>

namespace solid_edu
{
	TeacherGradeWindow::TeacherGradeWindow(std::unique_ptr<IUser> teacher, const Course& course, GradeMode mode)
		: teacher{ std::move(teacher) }, course{ course }, mode{ mode } {}

	std::unique_ptr<IWindow> TeacherGradeWindow::runThenReturnWindow()
	{
		std::unordered_set<std::string> studentsSet = course.GetStudents();
		std::vector<std::string> studentsVector{};
		std::copy(studentsSet.cbegin(), studentsSet.cend(), std::back_inserter(studentsVector));

		int counter = 0;

		for (auto& student : studentsVector)
		{
			counter++;
			std::cout << counter << ". " << student << std::endl;
		}

		int limes = counter;
		counter++;

		std::cout << "\n" << (counter + 1) << ". " << "Return to menu" << std::endl;

		int option = -1;
		std::cout << "> ";
		std::cin >> option;
		while ((std::cin.fail()) || option <= 0 || option > counter + 1)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Error: Please enter an option's number\n";
			std::cout << "> ";
			std::cin >> option;
		}

		if (option == counter + 1)
		{
			return std::unique_ptr<IWindow>{ new CourseContentsWindow(course, std::unique_ptr<IUser>{teacher->clone()}) };
		}
		else 
		{
			if (mode == GradeMode::Grade)
			{
				gradeStudent(studentsVector[option - 1]);
			}
			else
			{
				approveCompletionForStudent(studentsVector[option - 1]);
			}
			return std::unique_ptr<IWindow>{ new CourseContentsWindow(course, std::unique_ptr<IUser>{teacher->clone()}) };
		}
	}

	void TeacherGradeWindow::approveCompletionForStudent(const std::string& student)
	{
		std::ostringstream courseCompletionRecord{};
		courseCompletionRecord << course << "_false_" << 0;
		Factory::GetCompletedCoursesFileManager()->AddCompletedCourseInfoForUser(
			courseCompletionRecord.str(),
			student);
	}

	void TeacherGradeWindow::gradeStudent(const std::string& student)
	{
		std::cout << "Grade:" << std::endl;

		int option = -1;
		std::cout << "> ";
		std::cin >> option;
		while ((std::cin.fail()) || option <= 0 || option > 10)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Error: Please enter a valid passing grade [6-10]\n";
			std::cout << "> ";
			std::cin >> option;
		}

		if (option >= 6 && option <= 10)
		{
			std::ostringstream gradeRecord;
			gradeRecord << course << "_true_" << option;
			Factory::GetCompletedCoursesFileManager()->AddCompletedCourseInfoForUser(gradeRecord.str(), student);
		}
	}
}
