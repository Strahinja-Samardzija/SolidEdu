#pragma once

#include "stringlib.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <iostream>

namespace solid_edu
{
	static class Departments 
	{
	private:
		static std::string departmentsFileDestination;
		static std::unordered_map<std::string, std::unordered_set<std::string>> departmentToCourses;

	public:
		static void InitalizeDepartments();

		static bool isDepartmentRegistered(const std::string& department);

		static void RegisterDepartment(const std::string& departmentName, const std::vector<std::string>& courses);

		static void removeDepartment(const std::string& department);

		static void AddCourseToDepartment(const std::string& courseName, const std::string& department);

		static std::string departmentOf(const std::string& courseName);

		static void RemoveCourseFromDepartment(const std::string& courseName, const std::string& department);
	};
}
