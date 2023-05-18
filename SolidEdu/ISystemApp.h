#pragma once

#include "solid_edu_IConnectionsGraph.h"
#include "IUser.h"
#include <memory>
#include <string>
#include <unordered_set>

namespace solid_edu
{
	class ISystemApp
	{
	public:
		virtual bool CheckPassword(const std::string& username, const std::string& password) = 0;
		virtual std::unordered_set<std::string> GetCourses() = 0;
		virtual std::unique_ptr<IUser> getUser(const std::string& username) = 0;
		virtual bool isCourseRegistered(const std::string& courseName) = 0;
		virtual bool isUsernameRegistered(const std::string& username) = 0;
		virtual void RegisterCourse(const std::string& courseName) = 0;
		virtual void RegisterUser(const std::string& username, const std::string& password) = 0;
		virtual void RemoveCourse(const std::string& courseName) = 0;
		virtual void RemoveUser(const std::string& username) = 0;
		virtual std::shared_ptr<solid_edu::IConnectionsGraph> GetConnectionsGraph() = 0;

		virtual ~ISystemApp() = 0 {};
	};
}
