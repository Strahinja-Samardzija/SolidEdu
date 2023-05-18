#pragma once

#include "StringLib.h"
#include <string>
#include <unordered_map>
#include <tuple>

namespace solid_edu
{
	class ICompletedCoursesFileManager
	{
	public:
		virtual void AddCompletedCourseInfoForUser(const std::string& course_passed_grade_List, const std::string& username) = 0;
		virtual std::unordered_map<std::string, std::tuple<bool, int>> GetCompletedCoursesDictinaryForUser(const std::string& username) = 0;
		virtual void RemoveSingleCourseFromUsersCompletedCourses(const std::string& courseName, const std::string& username) = 0;
		virtual void RemoveUsersCompletedCoursesInfo(const std::string& username) = 0;
	};
}
