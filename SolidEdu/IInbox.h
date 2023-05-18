#pragma once

#include "IConversation.h"

#include <string>
#include <vector>
#include <memory>

namespace solid_edu
{
	class IInbox
	{
	public:
		virtual void notify(const std::string& messageSender) = 0;
		virtual std::unique_ptr<IConversation> getConversation(const std::string& aFriend) = 0;
		virtual std::vector<std::unique_ptr<IConversation>> getAllConversations(const std::vector<std::string>& friendUsers) = 0;
		virtual std::string getNotificationsBadge() = 0;
		virtual std::vector<std::string> getNotificationsPeers() = 0;
		virtual void removeConversations(const std::vector<std::string>& friends) = 0;
		virtual void RegisterUserSubscription() = 0;
		virtual void DeleteUserSubscription() = 0;

		virtual IInbox* clone() = 0;
		virtual ~IInbox() = 0 {};
	};
}
