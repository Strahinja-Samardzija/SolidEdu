#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <tuple>
#include "stringlib.h"
#include "ICompletedCoursesFileManager.h"

namespace solid_edu
{
	class CompletedCoursesFileManager : public ICompletedCoursesFileManager
	{
	public:
		std::unordered_map<std::string, std::tuple<bool, int>> GetCompletedCoursesDictinaryForUser(const std::string& username) override;

		void AddCompletedCourseInfoForUser(const std::string& course_passed_grade_List, const std::string& username) override;

		void RemoveSingleCourseFromUsersCompletedCourses(const std::string& courseName, const std::string& username) override;

		void RemoveUsersCompletedCoursesInfo(const std::string& username) override;
	};
}
