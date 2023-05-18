#pragma once

#include "StringLib.h"
#include "ICourseFileManager.h"
#include "Course.h"
#include <string>
#include <unordered_set>
#include <vector>
#include <iostream>

namespace solid_edu
{
	class CourseFileManager : public ICourseFileManager
	{
	public:
		void RegisterCourseInUsersLocalFile(
			const std::string& course,
			const std::string& user);

		void RegisterMultipleCoursesInUsersLocalFile(
			const std::vector<std::string>& courses,
			const std::string& user);

		void RemoveCoursesFromUsersLocalFile(
			const std::vector<std::string>& courses, 
			const std::string& user);
		
		std::unordered_set<std::string> GetAllCourses();

		Course_HashSet ReadCoursesForUser(const std::string& username);

		void DeleteLocalCoursesFileForUser(const std::string& username);

		void RegisterStudentToCourseInGlobalFile(
			const std::string& student,
			const std::string& courseName);

		void RegisterStudentToMultipleCoursesInGlobalFile(
			const std::string& student, 
			const std::vector<std::string>& courses);

		void RegisterUser(const std::string& username);

		void RegisterCourseInGlobalFile(const std::string& courseName);

		void RegisterTeacherToCourseInGlobalFile(
			const std::string& teacher, 
			const std::string& courseName);

		void RemoveCourseFromGlobalFile(const std::string& courseName);

		void RegisterTeacherToMultipleCoursesInGlobalFile(
			const std::string& teacher, 
			const std::vector<std::string>& courses);

		void RemoveStudentFromCoursesInGlobalFile(
			const std::string& student,
			const std::vector<std::string>& courses);

		void RemoveTeacherFromCoursesInGlobalFile(
			const std::string& teacher,
			const std::vector<std::string>& courses);

		std::unordered_set<std::string> ReadStudentsForCourse(const std::string& courseName);

		std::unordered_set<std::string> ReadTeachersForCourse(const std::string& courseName);

	private:
		std::string GetUsersCoursesFileDestination(const std::string& user);
		
		void RegisterUserToMultipleCoursesInCorrespondingGlobalFile(
			const std::string& user, 
			const std::vector<std::string>& courses,
			const std::string& globalFileDestination);

		void RemoveUserFromCoursesInCorrespondingGlobalFile(
			const std::string& user,
			const std::vector<std::string>& courses,
			const std::string& globalFileDestination);

		void RemoveCourseFromFile(
			const std::string& courseName,
			const std::string& file);

		std::string InsertUserInLine(
			const std::string& user,
			std::string& line);

		std::string DeleteUserFromLine(
			const std::string& user,
			std::string& line);
		
		std::unordered_set<std::string> ReadUsersForCourseFromCorrespondingGlobalFile(
			const std::string& courseName,
			const std::string& globalFileDestination);
	};
}
