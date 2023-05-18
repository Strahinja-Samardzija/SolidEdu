#include "CourseFileManager.h"
#include "Factory.h"
#include <regex>

namespace solid_edu
{
	void CourseFileManager::RegisterCourseInUsersLocalFile(const std::string& course, const std::string& user)
	{
		stringlib::appendAllLines(GetUsersCoursesFileDestination(user), std::vector<std::string> {course});
	}

	void CourseFileManager::RegisterMultipleCoursesInUsersLocalFile(const std::vector<std::string>& courses, const std::string& user)
	{
		stringlib::appendAllLines(GetUsersCoursesFileDestination(user), courses);
	}

	void CourseFileManager::RemoveCoursesFromUsersLocalFile(const std::vector<std::string>& courses, const std::string& user)
	{
		std::vector<std::string> coursesFromFile = stringlib::readAllLines(GetUsersCoursesFileDestination(user));

		auto p = std::remove_if(coursesFromFile.begin(), coursesFromFile.end(),
			[&courses](auto& aCourseFromFile)
			{
				return std::find(courses.cbegin(), courses.cend(), aCourseFromFile) != courses.end();
			}
		);
		if (p != coursesFromFile.end())
			coursesFromFile.erase(p, coursesFromFile.end());

		stringlib::writeAllLines(GetUsersCoursesFileDestination(user), coursesFromFile);
	}

	std::string CourseFileManager::GetUsersCoursesFileDestination(const std::string& user)
	{
		return Factory::GetSystemPathsDefault()->UserCoursesPath + user + "_classes.txt";
	}

	std::unordered_set<std::string> CourseFileManager::GetAllCourses()
	{
		std::unordered_set<std::string> courses{};
		std::vector<std::string> courseNames = 
			stringlib::readAllLines(Factory::GetSystemPathsDefault()->courseNamesFileDestination);
		for (auto& courseName : courseNames)
		{
			courses.insert(courseName);
		}

		return courses;
	}

	Course_HashSet CourseFileManager::ReadCoursesForUser(const std::string& username)
	{
		Course_HashSet myCourses{};

		std::vector<std::string> courses = stringlib::readAllLines(GetUsersCoursesFileDestination(username));
		for (auto& course : courses)
		{
			myCourses.insert(Course{ course });
		}

		return myCourses;
	}

	void CourseFileManager::DeleteLocalCoursesFileForUser(const std::string& username)
	{
		stringlib::deleteFile(GetUsersCoursesFileDestination(username));
	}

	void CourseFileManager::RegisterStudentToCourseInGlobalFile(const std::string& student, const std::string& courseName)
	{
		RegisterStudentToMultipleCoursesInGlobalFile(student, std::vector<std::string> {courseName});
	}

	void CourseFileManager::RegisterStudentToMultipleCoursesInGlobalFile(const std::string& student,
		const std::vector<std::string>& courses)
	{
		RegisterUserToMultipleCoursesInCorrespondingGlobalFile(student, courses,
			Factory::GetSystemPathsDefault()->courseStudentsFileDestination);
	}

	void CourseFileManager::RegisterUser(const std::string& username)
	{
		stringlib::createFile(GetUsersCoursesFileDestination(username));
	}

	void CourseFileManager::RegisterCourseInGlobalFile(const std::string& courseName)
	{
		stringlib::appendAllLines(Factory::GetSystemPathsDefault()->courseTeachersFileDestination, std::vector<std::string> { courseName + " - " });
		stringlib::appendAllLines(Factory::GetSystemPathsDefault()->courseStudentsFileDestination, std::vector<std::string> { courseName + " - " });
	}

	void CourseFileManager::RegisterTeacherToCourseInGlobalFile(const std::string& teacher, const std::string& courseName)
	{
		RegisterTeacherToMultipleCoursesInGlobalFile(teacher, std::vector<std::string> {courseName});
	}

	void CourseFileManager::RemoveCourseFromGlobalFile(const std::string& courseName)
	{
		RemoveCourseFromFile(courseName, Factory::GetSystemPathsDefault()->courseNamesFileDestination);
		RemoveCourseFromFile(courseName, Factory::GetSystemPathsDefault()->courseTeachersFileDestination);
		RemoveCourseFromFile(courseName, Factory::GetSystemPathsDefault()->courseStudentsFileDestination);
	}

	void CourseFileManager::RemoveCourseFromFile(const std::string& courseName, const std::string& file)
	{
		std::vector<std::string> lines = stringlib::readAllLines(file);

		auto p = std::remove_if(lines.begin(), lines.end(),
			[&courseName](auto& line)
			{
				return stringlib::startsWith(line, courseName);
			}
		);
		if (p != lines.end())
			lines.erase(p, lines.end());

		stringlib::writeAllLines(file, lines);
	}

	void CourseFileManager::RegisterTeacherToMultipleCoursesInGlobalFile(
		const std::string& teacher,
		const std::vector<std::string>& courses)
	{
		RegisterUserToMultipleCoursesInCorrespondingGlobalFile(teacher, courses,
			Factory::GetSystemPathsDefault()->courseTeachersFileDestination);
	}

	void CourseFileManager::RemoveStudentFromCoursesInGlobalFile(
		const std::string& student,
		const std::vector<std::string>& courses)
	{
		RemoveUserFromCoursesInCorrespondingGlobalFile(student, courses,
			Factory::GetSystemPathsDefault()->courseStudentsFileDestination);
	}

	void CourseFileManager::RemoveTeacherFromCoursesInGlobalFile(
		const std::string& teacher,
		const std::vector<std::string>& courses)
	{
		RemoveUserFromCoursesInCorrespondingGlobalFile(teacher, courses,
			Factory::GetSystemPathsDefault()->courseTeachersFileDestination);
	}

	void CourseFileManager::RegisterUserToMultipleCoursesInCorrespondingGlobalFile(
		const std::string& user,
		const std::vector<std::string>& courses,
		const std::string& globalFileDestination)
	{
		std::vector<std::string> lines = stringlib::readAllLines(globalFileDestination);

		std::transform(lines.begin(), lines.end(), lines.begin(),
			[&](std::string& line) -> std::string
			{
				auto thisLinesCourse = stringlib::trim(line.substr(0, line.find("-")));
				if (std::find(courses.cbegin(), courses.cend(), thisLinesCourse) != courses.cend())
				{
					return InsertUserInLine(user, line);
				}
				else
				{
					return line;
				}
			}
		);

		stringlib::writeAllLines(globalFileDestination, lines);
	}

	void CourseFileManager::RemoveUserFromCoursesInCorrespondingGlobalFile(const std::string& user, const std::vector<std::string>& courses, const std::string& globalFileDestination)
	{
		std::vector<std::string> lines = stringlib::readAllLines(globalFileDestination);

		std::regex userRegex{ R"(\b)" + user + R"(\b)" };
		for (int i = 0; i < lines.size(); i++)
		{
			for (auto& course : courses)
			{
				if (stringlib::startsWith(lines[i], course) && std::regex_search(lines[i], userRegex))
				{
					lines[i] = DeleteUserFromLine(user, lines[i]);
					break;
				}
			}
		}

		stringlib::writeAllLines(globalFileDestination, lines);
	}

	std::string CourseFileManager::InsertUserInLine(const std::string& user, std::string& line)
	{
		if (stringlib::endsWith(line, "-"))
		{
			line += " " + user;
		}
		else
		{
			line += ", " + user;
		}

		return line;
	}

	std::string CourseFileManager::DeleteUserFromLine(const std::string& user, std::string& line)
	{
		std::regex userRegex{ R"(\b)" + user + R"((,|\b))" };
		line = std::regex_replace(line, userRegex, "");
		return line;
	}

	std::unordered_set<std::string> CourseFileManager::ReadStudentsForCourse(const std::string& courseName)
	{
		return ReadUsersForCourseFromCorrespondingGlobalFile(courseName,
			Factory::GetSystemPathsDefault()->courseStudentsFileDestination);
	}

	std::unordered_set<std::string> CourseFileManager::ReadTeachersForCourse(const std::string& courseName)
	{
		return ReadUsersForCourseFromCorrespondingGlobalFile(courseName,
			Factory::GetSystemPathsDefault()->courseTeachersFileDestination);
	}

	std::unordered_set<std::string> CourseFileManager::ReadUsersForCourseFromCorrespondingGlobalFile(
		const std::string& courseName,
		const std::string& globalFileDestination)
	{
		std::unordered_set<std::string> users{};

		std::vector<std::string> lines = stringlib::readAllLines(globalFileDestination);

		for (int i = 0; i < lines.size(); i++)
		{
			if (courseName == stringlib::trim(lines[i].substr(0, lines[i].find("-"))))
			{
				if (stringlib::endsWith(lines[i], "-"))
				{
					return std::unordered_set<std::string>();
				}

				std::vector<std::string> readUsers = stringlib::split(lines[i].substr(lines[i].find("-") + 1), ',');
				for (auto& user : readUsers)
				{
					users.insert(user);
				}
				break;
			}
		}

		return users;
	}
}