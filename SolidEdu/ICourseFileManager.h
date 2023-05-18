#pragma once

//todo make it really interface like
// and then renew implementations from ISystemApp for registration

#include "Course.h"
#include <string>
#include <unordered_set>

namespace solid_edu
{
	class ICourseFileManager
	{
	public:
		virtual void DeleteLocalCoursesFileForUser(const std::string& username) = 0;
		virtual std::unordered_set<std::string> GetAllCourses() = 0;
		virtual std::unordered_set<Course, std::hash<Course>, std::equal_to<Course>> ReadCoursesForUser(const std::string& username) = 0;
		virtual std::unordered_set<std::string> ReadStudentsForCourse(const std::string& courseName) = 0;
		virtual std::unordered_set<std::string> ReadTeachersForCourse(const std::string& courseName) = 0;
		virtual void RegisterCourseInGlobalFile(const std::string& courseName) = 0;
		virtual void RegisterCourseInUsersLocalFile(const std::string& course, const std::string& user) = 0;
		virtual void RegisterMultipleCoursesInUsersLocalFile(const std::vector<std::string>& courses, const std::string& user) = 0;
		virtual void RegisterStudentToCourseInGlobalFile(const std::string& student, const std::string& courseName) = 0;
		virtual void RegisterStudentToMultipleCoursesInGlobalFile(const std::string& student, const std::vector<std::string>& courses) = 0;
		virtual void RegisterTeacherToCourseInGlobalFile(const std::string& teacher, const std::string& courseName) = 0;
		virtual void RegisterTeacherToMultipleCoursesInGlobalFile(const std::string& teacher, const std::vector<std::string>& courses) = 0;
		virtual void RegisterUser(const std::string& username) = 0;
		virtual void RemoveCourseFromGlobalFile(const std::string& courseName) = 0;
		virtual void RemoveCoursesFromUsersLocalFile(const std::vector<std::string>& courses, const std::string& user) = 0;
		virtual void RemoveStudentFromCoursesInGlobalFile(const std::string& student, const std::vector<std::string>& courses) = 0;
		virtual void RemoveTeacherFromCoursesInGlobalFile(const std::string& teacher, const std::vector<std::string>& courses) = 0;

		virtual ~ICourseFileManager() = 0 {};
	};
}
