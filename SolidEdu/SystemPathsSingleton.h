#pragma once

#include "SystemPathsBase.h"
#include <memory>
#include <string>

namespace solid_edu
{
	class SystemPathsSingleton : public SystemPathsBase
	{
	private:
		static std::shared_ptr<SystemPathsBase> unique;

		SystemPathsSingleton(const std::string& InboxPath, const std::string& UserCoursesPath, const std::string& courseObjectPath, const std::string& prerequisitesForCoursePath, const std::string& courseNamesFileDestination, const std::string& usernameToPasswordFileDestionation, const std::string& graphFileDestination, const std::string& courseStudentsFileDestination, const std::string& passedCoursesFileDestination, const std::string& courseTeachersFileDestination);

	public:
		static std::shared_ptr<SystemPathsBase> GetInstance(const std::string& fileDestination);

		static std::shared_ptr<SystemPathsBase> GetInstance();

		std::string GetCourseApplicationRequestsFileDestination(const std::string& courseName) override;

		std::string GetFriendRequestsFileDestination(const std::string& username) override;
	};
}
