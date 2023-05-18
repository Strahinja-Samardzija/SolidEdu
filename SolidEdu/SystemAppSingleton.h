#pragma once

#include "ISystemApp.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace solid_edu
{
	class SystemAppSingleton : public ISystemApp
	{
	private:
		static std::shared_ptr<ISystemApp> unique;

		static std::unordered_set<std::string> courses;
		static std::unordered_set<std::string> usernames;
		static std::unordered_map<std::string, std::string> usernameToPassword;
		static std::shared_ptr<IConnectionsGraph> connectionsGraph;

		SystemAppSingleton();

	public:
		static std::shared_ptr<ISystemApp> GetInstance();

	private:
		void initialize();

		void initializeCourses();

	public:
		std::shared_ptr<IConnectionsGraph> GetConnectionsGraph() override;
		
		bool CheckPassword(const std::string& username, const std::string& password) override;
		
		std::unique_ptr<IUser> getUser(const std::string& username) override;
		std::unordered_set<std::string> GetCourses() override;

		bool isCourseRegistered(const std::string& courseName) override;
		bool isUsernameRegistered(const std::string& username) override;

		void RegisterUser(const std::string& username, const std::string& password) override;
		void RegisterCourse(const std::string& courseName) override;

		void RemoveUser(const std::string& username) override;
		void RemoveCourse(const std::string& courseName) override;

	private:
		void initializeUsernamesAndPasswords();
		void RemoveFromUserPaswordFile(const std::string& username);
	};
}
