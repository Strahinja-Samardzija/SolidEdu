#pragma once

#include "IInbox.h"
#include "INotifier.h"
#include "Factory.h"
#include <string>
#include <vector>

namespace solid_edu
{
	class Inbox : public IInbox
	{
	private:
		std::string owner;
		std::unique_ptr<INotifier> notifier;
		std::string notificationsFileDestination;

	public:
		Inbox(const std::string& owner);

		Inbox* clone() override;

	private:
		inline std::string getNotificationsFileDestination();

	public:
		std::string getNotificationsBadge();

		std::vector<std::string> getNotificationsPeers();

		std::unique_ptr<IConversation> getConversation(const std::string& aFriend);

		// friendUsers include every user one can send messages to
		std::vector<std::unique_ptr<IConversation>> getAllConversations(const std::vector<std::string>& friendUsers) override;

	private:
		std::vector<std::string> convertToFileDestinations(const std::string& username, const std::vector<std::string>& friendUsers);

	public:
		void removeConversations(const std::vector<std::string>& friends);

		void RegisterUserSubscription();

		void DeleteUserSubscription();

		void notify(const std::string& messageSender);
	};
}
