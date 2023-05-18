#include "SystemAppSingleton.h"
#include "PrerequisiteTypes.h"
#include "Factory.h"
#include "Departments.h"
#include "User.h"

namespace solid_edu
{
	std::shared_ptr<ISystemApp> SystemAppSingleton::unique{ nullptr };
	std::unordered_set<std::string> SystemAppSingleton::courses{};
	std::unordered_set<std::string> SystemAppSingleton::usernames{};
	std::unordered_map<std::string, std::string> SystemAppSingleton::usernameToPassword{};
	std::shared_ptr<IConnectionsGraph> SystemAppSingleton::connectionsGraph
	{ Factory::GetConnectionsGraph(Factory::GetSystemPathsDefault()->graphFileDestination) };

	SystemAppSingleton::SystemAppSingleton()
	{
		initialize();
	}

	std::shared_ptr<ISystemApp> SystemAppSingleton::GetInstance()
	{
		if (unique == nullptr)
		{
			unique = std::unique_ptr<ISystemApp>{ new SystemAppSingleton() };
		}
		return unique;
	}

	void SystemAppSingleton::initialize()
	{
		initializeCourses();
		initializeUsernamesAndPasswords();
		Departments::InitalizeDepartments();
	}

	void SystemAppSingleton::initializeCourses()
	{
		courses = Factory::GetCourseFileManager()->GetAllCourses();
	}

	std::shared_ptr<solid_edu::IConnectionsGraph> SystemAppSingleton::GetConnectionsGraph()
	{
		return connectionsGraph;
	}

	bool SystemAppSingleton::isCourseRegistered(const std::string& courseName)
	{
		return std::find(courses.begin(), courses.end(), courseName) != courses.end();
	}

	void SystemAppSingleton::RemoveUser(const std::string& username)
	{
		std::unique_ptr<IUser> user{};
		try
		{
			user = getUser(username);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what();
			throw std::runtime_error{ "Could not remove user " + username + "." };
		}
		auto courses = user->getCourses();
		std::vector<std::string> coursesHeTeaches;
		std::vector<std::string> coursesHeStudies;

		for (auto& course : courses)
		{
			std::ostringstream courseName{};
			courseName << course;
			if (course.hasTeacher(username))
			{
				coursesHeTeaches.push_back(courseName.str());
			}
			else
			{
				coursesHeStudies.push_back(courseName.str());
			}
		}

		Factory::GetInbox(username)->DeleteUserSubscription();
		Factory::GetNotifierForFriendRequests(username)->DeleteUsersFriendRequestSubscription();
		Factory::GetConnectionsManager()->RemoveUser(username);

		Factory::GetCompletedCoursesFileManager()->RemoveUsersCompletedCoursesInfo(username);

		auto courseFileManager = Factory::GetCourseFileManager();
		courseFileManager->RemoveTeacherFromCoursesInGlobalFile(username, coursesHeTeaches);
		courseFileManager->RemoveStudentFromCoursesInGlobalFile(username, coursesHeStudies);
		courseFileManager->DeleteLocalCoursesFileForUser(username);

		RemoveFromUserPaswordFile(username);
		usernameToPassword.erase(username);
		usernames.erase(username);
	}

	void SystemAppSingleton::RemoveFromUserPaswordFile(const std::string& username)
	{
		auto lines = stringlib::readAllLines(Factory::GetSystemPathsDefault()->usernameToPasswordFileDestionation);
		for (int i = 0; i < lines.size(); i++)
		{
			if (stringlib::startsWith(lines[i], username + "_"))
			{
				lines.erase(lines.begin() + i);
				break;
			}
		}

		stringlib::writeAllLines(Factory::GetSystemPathsDefault()->usernameToPasswordFileDestionation, lines);
	}

	void SystemAppSingleton::RegisterUser(const std::string& username, const std::string& password)
	{
		usernames.insert(username);
		usernameToPassword.emplace(username, password);
		stringlib::appendAllLines(Factory::GetSystemPathsDefault()->usernameToPasswordFileDestionation,
			std::vector<std::string> {
			username + "_" + password
		});

		Factory::GetConnectionsManager()->RegisterUser(username);

		Factory::GetNotifierForFriendRequests(username)->RegisterUsersFriendRequestSubscription();
		Factory::GetInbox(username)->RegisterUserSubscription();
		Factory::GetCourseFileManager()->RegisterUser(username);
	}

	void SystemAppSingleton::RegisterCourse(const std::string& courseName)
	{
		courses.insert(courseName);
		stringlib::appendAllLines(Factory::GetSystemPathsDefault()->courseNamesFileDestination,
			std::vector<std::string> {
			courseName
		});
		Factory::GetCourseFileManager()->RegisterCourseInGlobalFile(courseName);

		Factory::GetNotifierForCourseApplicationRequests(courseName)->RegisterCourseSubscription();
		PrerequisiteTypes::RegisterCourseSubscription(courseName);
	}

	void SystemAppSingleton::RemoveCourse(const std::string& courseName)
	{
		Course course{ courseName };
		course.RemoveSelf();

		courses.erase(courseName);
	}

	bool SystemAppSingleton::isUsernameRegistered(const std::string& username)
	{
		return std::find(usernames.begin(), usernames.end(), username) != usernames.end();
	}

	void SystemAppSingleton::initializeUsernamesAndPasswords()
	{
		std::vector<std::string> lines = stringlib::readAllLines(Factory::GetSystemPathsDefault()
			->usernameToPasswordFileDestionation);
		if (lines.empty())
		{
			return;
		}

		for (auto& line : lines)
		{
			auto username_password = stringlib::split(line, '_');
			usernames.insert(username_password[0]);
			usernameToPassword.emplace(username_password[0], username_password[1]);
		}
	}

	bool SystemAppSingleton::CheckPassword(const std::string& username, const std::string& password)
	{
		return std::find(usernames.begin(), usernames.end(), username) != usernames.end() && usernameToPassword[username] == password;
	}

	std::unique_ptr<IUser> SystemAppSingleton::getUser(const std::string& username) throw (std::exception)
	{
		return std::unique_ptr<IUser>{ new User(username, usernameToPassword[username]) };
	}

	std::unordered_set<std::string> SystemAppSingleton::GetCourses()
	{
		return courses;
	}
}
