#include "SystemPathsSingleton.h"

namespace solid_edu
{
	std::shared_ptr<SystemPathsBase> SystemPathsSingleton::unique{nullptr};

	SystemPathsSingleton::SystemPathsSingleton(
		const std::string& InboxPath, 
		const std::string& UserCoursesPath, 
		const std::string& courseObjectPath, 
		const std::string& prerequisitesForCoursePath, 
		const std::string& courseNamesFileDestination, 
		const std::string& usernameToPasswordFileDestionation, 
		const std::string& graphFileDestination, 
		const std::string& courseStudentsFileDestination, 
		const std::string& passedCoursesFileDestination, 
		const std::string& courseTeachersFileDestination
	) 
		: SystemPathsBase(
			InboxPath, 
			UserCoursesPath, 
			courseObjectPath, 
			prerequisitesForCoursePath, 
			courseNamesFileDestination, 
			usernameToPasswordFileDestionation, 
			graphFileDestination, 
			courseStudentsFileDestination, 
			passedCoursesFileDestination, 
			courseTeachersFileDestination
		)
	{}

	std::shared_ptr<SystemPathsBase> SystemPathsSingleton::GetInstance(const std::string& fileDestination)
	{
		//todo read from file
		return GetInstance();
	}

	std::shared_ptr<SystemPathsBase> SystemPathsSingleton::GetInstance()
	{
		if (unique == nullptr)
		{
			std::string InboxPath = "";
			std::string UserCoursesPath = "";
			std::string courseObjectPath = "";
			std::string prerequisitesForCoursePath = "";
			std::string courseNamesFileDestination = "courses.txt";
			std::string usernameToPasswordFileDestionation = "user_password.txt";
			std::string graphFileDestination = "connections.txt";

			std::string courseStudentsFileDestination = "courseStudents.txt";
			std::string passedCoursesFileDestination = "passedCourses.txt";
			std::string courseTeachersFileDestination = "courseTeachers.txt";

			unique = std::shared_ptr<SystemPathsBase>{
				new SystemPathsSingleton(
					InboxPath,
					UserCoursesPath,
					courseObjectPath,
					prerequisitesForCoursePath,
					courseNamesFileDestination,
					usernameToPasswordFileDestionation,
					graphFileDestination,
					courseStudentsFileDestination,
					passedCoursesFileDestination,
					courseTeachersFileDestination)
			};
		}
		return unique;
	}

	std::string SystemPathsSingleton::GetCourseApplicationRequestsFileDestination(const std::string& courseName)
	{
		return courseObjectPath + courseName + "_requests.txt";
	}

	std::string SystemPathsSingleton::GetFriendRequestsFileDestination(const std::string& username)
	{
		return courseObjectPath + username + "_requests.txt";
	}
}
