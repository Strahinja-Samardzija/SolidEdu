#include "CompletedCoursesFileManager.h"
#include "Factory.h"
#include <regex>

namespace solid_edu
{
	std::unordered_map<std::string, std::tuple<bool, int>>
		CompletedCoursesFileManager::GetCompletedCoursesDictinaryForUser(const std::string& username)
	{
		std::unordered_map<std::string, std::tuple<bool, int>> courseTo_passedBool_gradeInt_{};

		std::vector<std::string> lines =
			stringlib::readAllLines(Factory::GetSystemPathsDefault()->passedCoursesFileDestination);

		for (auto& line : lines)
		{
			if (stringlib::startsWith(line, username))
			{
				if (stringlib::endsWith(line, ":"))
				{
					return std::unordered_map<std::string, std::tuple<bool, int>>{};
				}

				std::vector<std::string> argsForGrades = stringlib::split(line.substr(line.find(":") + 1), ';');

				for (auto& argument : argsForGrades)
				{
					std::string courseName = argument.substr(0, argument.find("_"));
					std::string rest = argument.substr(argument.find("_") + 1);
					std::string boolPassedString = rest.substr(0, (int)rest.find("_"));
					std::string intGradeString = rest.substr(rest.find("_") + 1);

					bool passed = boolPassedString == "true" ? true : false;

					int grade{};
					std::istringstream convertFromString{ intGradeString };
					convertFromString >> grade;

					courseTo_passedBool_gradeInt_[courseName] = std::make_tuple(passed, grade);
				}
				break;
			}
		}

		return courseTo_passedBool_gradeInt_;
	}

	void CompletedCoursesFileManager::AddCompletedCourseInfoForUser(const std::string& course_passed_grade_List, const std::string& username)
	{
		std::vector<std::string> lines = stringlib::readAllLines(Factory::GetSystemPathsDefault()->passedCoursesFileDestination);
		if (lines.empty())
		{
			stringlib::writeAllLines(Factory::GetSystemPathsDefault()->passedCoursesFileDestination,
				std::vector<std::string> {
				username + ":" + course_passed_grade_List
			});
			return;
		}

		auto p = std::find_if(lines.cbegin(), lines.cend(),
			[&username](auto& line)
			{
				return stringlib::startsWith(line, username);
			}
		);

		if (p == lines.cend())
		{
			lines.push_back(username + ":" + course_passed_grade_List);
			stringlib::writeAllLines(Factory::GetSystemPathsDefault()->passedCoursesFileDestination, lines);
			return;
		}
		else
		{
			if (stringlib::endsWith(*p, ":"))
			{
				lines[p - lines.cbegin()] += course_passed_grade_List;
			}
			else
			{
				lines[p - lines.cbegin()] += ";" + course_passed_grade_List;
			}
			stringlib::writeAllLines(Factory::GetSystemPathsDefault()->passedCoursesFileDestination, lines);
			return;
		}
	}

	void CompletedCoursesFileManager::RemoveSingleCourseFromUsersCompletedCourses(const std::string& courseName, const std::string& username)
	{
		std::vector<std::string> lines = stringlib::readAllLines(Factory::GetSystemPathsDefault()->passedCoursesFileDestination);

		std::regex courseRecordRegex{ R"(\b)" + courseName + R"(_(true|false)_[0-9]*(;|\b))"};
		// non const reference, we are removing a course from it
		for (std::string& line : lines)
		{
			if (stringlib::startsWith(line, username + ":"))
			{
				line = std::regex_replace(line, courseRecordRegex, "");
			}
		}

		stringlib::writeAllLines(Factory::GetSystemPathsDefault()->passedCoursesFileDestination, lines);
	}

	void CompletedCoursesFileManager::RemoveUsersCompletedCoursesInfo(const std::string& username)
	{
		std::vector<std::string> lines = stringlib::readAllLines(Factory::GetSystemPathsDefault()->passedCoursesFileDestination);

		auto iterator = std::remove_if(lines.begin(), lines.end(),
			[&username](auto& line)
			{
				return stringlib::startsWith(line, username);
			}
		);
		if (iterator != lines.end())
			lines.erase(iterator, lines.end());

		stringlib::writeAllLines(Factory::GetSystemPathsDefault()->passedCoursesFileDestination, lines);
	}
}
