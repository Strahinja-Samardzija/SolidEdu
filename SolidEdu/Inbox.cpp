#include "Inbox.h"
#include "StringLib.h"
#include <algorithm>


namespace solid_edu
{
	Inbox::Inbox(const std::string& owner) : owner{ owner }, notificationsFileDestination{}, notifier{}
	{
		notificationsFileDestination = Factory::GetSystemPathsDefault()->InboxPath + owner + "_notifications.txt";
		notifier = Factory::getNotifierForFileStorageInbox(notificationsFileDestination);
	}

	Inbox* Inbox::clone()
	{
		return new Inbox(owner);
	}

	std::string Inbox::getNotificationsFileDestination()
	{
		return notificationsFileDestination;
	}

	std::string Inbox::getNotificationsBadge()
	{
		return notifier->getNotificationsBadge();
	}

	std::vector<std::string> Inbox::getNotificationsPeers()
	{
		return notifier->getNotificationsPeers();
	}

	std::unique_ptr<IConversation> Inbox::getConversation(const std::string& aFriend)
	{
		std::vector<std::string> friendVector{ aFriend };
		auto fileDestinations{ convertToFileDestinations(owner, friendVector) };
		return Factory::GetConversation(fileDestinations[0]);
	}

	std::vector<std::unique_ptr<IConversation>> Inbox::getAllConversations(const std::vector<std::string>& friendUsers)
	{
		std::vector<std::string> fileDestinations = convertToFileDestinations(owner, friendUsers);
		std::vector<std::unique_ptr<IConversation>> conversations;

		for (auto& fileDest : fileDestinations)
		{
			conversations.emplace_back(Factory::GetConversation(fileDest));
		}
		return conversations;
	}

	std::vector<std::string> Inbox::convertToFileDestinations(const std::string& username, const std::vector<std::string>& friendUsers)
	{
		auto fileDestinations = std::vector<std::string>();
		for (auto& aFriend : friendUsers)
		{
			auto friends = std::minmax(aFriend, username);
			fileDestinations.push_back(Factory::GetSystemPathsDefault()->InboxPath + friends.first + "_" + friends.second + "_.txt");
		}
		return fileDestinations;
	}

	void Inbox::removeConversations(const std::vector<std::string>& friends)
	{
		auto conversations = convertToFileDestinations(owner, friends);
		for (auto& conversationFile : conversations)
		{
			if (stringlib::fileExists(conversationFile))
			{
				stringlib::deleteFile(conversationFile);
			}
		}
	}

	void Inbox::RegisterUserSubscription()
	{
		stringlib::writeAllLines(getNotificationsFileDestination(), std::vector<std::string>{});
	}

	void Inbox::DeleteUserSubscription()
	{
		try
		{
			stringlib::deleteFile(getNotificationsFileDestination());
		}
		catch (stringlib::bad_filename)
		{
			std::cerr << "Error: Subscription details (Inbox) for owner: " << owner << " are currently unavailable.\n";
		}

		std::vector<std::string> teachers{};
		try
		{
			auto courses = Factory::GetUser(owner)->getCourses();
			for (const auto& course : courses)
			{
				for (auto& teacher : course.GetTeachers())
				{
					teachers.push_back(teacher);
				}
			}
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what();
		}

		std::sort(teachers.begin(), teachers.end());
		auto p = std::unique(teachers.begin(), teachers.end());

		if (p != teachers.end())
			teachers.erase(p);

		// delete teacher files
		for (auto& conversationFile :
			convertToFileDestinations(owner, Factory::GetConnectionsManager()->GetFriends(owner)))
		{
			if (stringlib::fileExists(conversationFile))
			{
				stringlib::deleteFile(conversationFile);
			}
		}

		// delete friend files
		for (auto& conversationFile :
			convertToFileDestinations(owner, Factory::GetConnectionsManager()->GetFriends(owner)))
		{
			if (stringlib::fileExists(conversationFile))
			{
				stringlib::deleteFile(conversationFile);
			}
		}
	}

	void Inbox::notify(const std::string& messageSender)
	{
		notifier->notify(messageSender);
	}
}
