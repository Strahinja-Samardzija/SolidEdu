#include "StudentDecorator.h"
#include "Factory.h"

namespace solid_edu
{
	StudentDecorator::StudentDecorator(std::unique_ptr<IUser> user) : userWrappee{ std::move(user) },
		course_to_boolPassed_intGrade{}
	{
		InitializeCompletedCourses();
	}

	StudentDecorator* StudentDecorator::clone()
	{
		return new StudentDecorator(std::unique_ptr<IUser>{userWrappee->clone()});
	}

	void StudentDecorator::InitializeCompletedCourses()
	{
		course_to_boolPassed_intGrade = Factory::GetCompletedCoursesFileManager()
			->GetCompletedCoursesDictinaryForUser(userWrappee->getUsername());
	}

	bool StudentDecorator::hasCompletedCourse(const std::string& courseName) const
	{
		return course_to_boolPassed_intGrade.find(courseName) != course_to_boolPassed_intGrade.end();
	}

	std::vector<std::string> StudentDecorator::getAllCompletedCourses() const
	{
		std::vector<std::string> courses;
		for (auto& key_val : course_to_boolPassed_intGrade)
		{
			courses.push_back(key_val.first);
		}
		return courses;
	}

	std::vector<std::tuple<std::string, int>> StudentDecorator::getAllGrades() const
	{
		std::vector<std::tuple<std::string, int>> grades{};
		for (const auto& key_val : course_to_boolPassed_intGrade)
		{
			bool passed = std::get<0>(course_to_boolPassed_intGrade.at(key_val.first));
			int grade = std::get<1>(course_to_boolPassed_intGrade.at(key_val.first));
			if (passed)
			{
				grades.emplace_back(key_val.first, grade);
			}
		}

		return grades;
	}

	int StudentDecorator::GetGradeInCourse(const std::string& courseName) const
	{
		if (hasCompletedCourse(courseName))
		{
			if (std::get<0>(course_to_boolPassed_intGrade.at(courseName)))
			{
				return std::get<1>(course_to_boolPassed_intGrade.at(courseName));
			}
		}
		// else 
		return 0;
	}

	void StudentDecorator::changePassword(const std::string& newPassword)
	{
		userWrappee->changePassword(newPassword);
	}

	Course_HashSet StudentDecorator::getCourses() const
	{
		return userWrappee->getCourses();
	}

	std::unique_ptr<IInbox> StudentDecorator::getInbox() const
	{
		return userWrappee->getInbox();
	}

	std::string StudentDecorator::getUsername() const
	{
		return userWrappee->getUsername();
	}
}
