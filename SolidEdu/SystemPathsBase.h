#pragma once

#include <string>

namespace solid_edu
{
	class SystemPathsBase
	{
	public:
		const std::string InboxPath;
		const std::string UserCoursesPath;
		const std::string courseObjectPath;
		const std::string prerequisitesForCoursePath;
		const std::string courseNamesFileDestination;
		const std::string usernameToPasswordFileDestionation;
		const std::string graphFileDestination;

		const std::string courseStudentsFileDestination;
		const std::string passedCoursesFileDestination;
		const std::string courseTeachersFileDestination;

	protected:
		SystemPathsBase(
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
			: InboxPath{ InboxPath },
			UserCoursesPath{ UserCoursesPath },
			courseObjectPath{ courseObjectPath },
			prerequisitesForCoursePath{ prerequisitesForCoursePath },
			courseNamesFileDestination{ courseNamesFileDestination },
			usernameToPasswordFileDestionation{ usernameToPasswordFileDestionation },
			graphFileDestination{ graphFileDestination },
			courseStudentsFileDestination{ courseStudentsFileDestination },
			passedCoursesFileDestination{ passedCoursesFileDestination },
			courseTeachersFileDestination{ courseTeachersFileDestination } {}

	public:
		virtual std::string GetCourseApplicationRequestsFileDestination(const std::string& courseName) = 0;
		virtual std::string GetFriendRequestsFileDestination(const std::string& username) = 0;

		virtual ~SystemPathsBase() = 0 {};
	};
}
