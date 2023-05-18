#pragma once

#include <string>
#include <vector>

namespace solid_edu
{
	class INotifier
	{
	public:
		virtual std::string getNotificationsBadge() = 0;
		virtual std::vector<std::string> getNotificationsPeers() = 0;
		virtual void notify(const std::string& senderUsername) = 0;
		virtual void RegisterCourseSubscription() = 0;
		virtual void RegisterUsersFriendRequestSubscription() = 0;
		virtual void DeleteCourseSubscription() = 0;
		virtual void DeleteUsersFriendRequestSubscription() = 0;

		virtual ~INotifier() = 0 {};
	};
}
