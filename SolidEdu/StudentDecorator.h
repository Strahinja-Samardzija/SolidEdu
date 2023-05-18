#pragma once

#include "IUser.h"
#include "Course.h"

#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>	
#include <tuple>

namespace solid_edu
{
	class StudentDecorator : public IUser
	{
		using mapCourseGradeAlias = std::unordered_map <std::string, std::tuple <bool, int>>;

		std::unique_ptr<IUser> userWrappee;

		// the existance of a key means that the course which is the key has been completed
		// if value.Item1 is true then the course is passed too
		mapCourseGradeAlias course_to_boolPassed_intGrade{ mapCourseGradeAlias{} };
	
	public:
		StudentDecorator(std::unique_ptr<IUser> user);

		StudentDecorator* clone() override;

	public:
		inline bool hasCompletedCourse(const std::string& courseName) const;

		std::vector<std::string> getAllCompletedCourses() const;

		std::vector<std::tuple<std::string, int>> getAllGrades() const;

		int GetGradeInCourse(const std::string& courseName) const;

		void changePassword(const std::string& newPassword) override;

		Course_HashSet getCourses() const override;

		inline std::unique_ptr<IInbox> getInbox() const override;

		inline std::string getUsername() const override;

	private:
		void InitializeCompletedCourses();
	};
}