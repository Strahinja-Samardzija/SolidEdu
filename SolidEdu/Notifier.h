#pragma once

#include "INotifier.h"
#include "Factory.h"

#include <string>
#include <vector>

namespace solid_edu
{
	class Notifier : public INotifier
	{
	private:
		std::string notificationsFileDestination;

	public:
		Notifier(const std::string& notificationsFileDestination);

		void notify(const std::string& senderUsername) override;

		std::string getNotificationsBadge() override;

		std::vector<std::string> getNotificationsPeers() override;

		void RegisterCourseSubscription() override;

		void DeleteCourseSubscription() override;

		void RegisterUsersFriendRequestSubscription() override;

		void DeleteUsersFriendRequestSubscription() override;
	};
}

