#include "Factory.h"
#include "FeatureSelector.h"
#include "CourseFileManager.h"
#include "User.h"
#include "MessageReader.h"
#include "Conversation.h"
#include "Inbox.h"
#include "Notifier.h"
#include "SystemAppSingleton.h"
#include "SystemPathsSingleton.h"
#include "CompletedCoursesFileManager.h"
#include "ConnectionsManager.h"
#include "ConnectionsGraphAdapterFromLibrary.h"

namespace solid_edu
{
	std::unique_ptr<IInbox> Factory::GetInbox(const std::string& user)
	{
		return std::unique_ptr<IInbox>{new Inbox(user)};
	}

	std::unique_ptr <ICourseFileManager> Factory::GetCourseFileManager()
	{
		return std::unique_ptr <ICourseFileManager>{new CourseFileManager()};
	}

	std::unique_ptr <ICompletedCoursesFileManager> Factory::GetCompletedCoursesFileManager()
	{
		return std::unique_ptr <ICompletedCoursesFileManager>{new CompletedCoursesFileManager()};
	}

	std::unique_ptr <IFeatureSelector> Factory::GetFeatureSelector()
	{
		return std::unique_ptr <IFeatureSelector>{new FeatureSelector()};
	}

	std::shared_ptr <IConnectionsGraph> Factory::GetConnectionsGraph(const std::string& fileDestination)
	{
		auto ptr = std::shared_ptr<connections_graph::ConnectionsGraph>(
			new connections_graph::ConnectionsGraph{ Factory::GetSystemPathsDefault()->graphFileDestination }
		);
		return std::shared_ptr<IConnectionsGraph>{new ConnectionsGraphAdapterFromLibrary{ ptr }};
	}

	std::shared_ptr <SystemPathsBase> Factory::GetSystemPathsFromFile(const std::string& fileDestination)
	{
		return SystemPathsSingleton::GetInstance(fileDestination);
	}

	std::shared_ptr <SystemPathsBase> Factory::GetSystemPathsDefault()
	{
		return SystemPathsSingleton::GetInstance();
	}

	std::shared_ptr <IConnectionsManager> Factory::GetConnectionsManager()
	{
		return std::shared_ptr <IConnectionsManager>{new ConnectionsManager()};
	}

	std::unique_ptr <IConversation> Factory::GetConversation(const std::string& conversationFileDestination)
	{
		return std::unique_ptr <IConversation>{Conversation::GetConversation(conversationFileDestination)};
	}

	std::unique_ptr <INotifier> Factory::getNotifierForFileStorageInbox(const std::string& notificationsFileDestination)
	{
		return std::unique_ptr <INotifier>{new Notifier(notificationsFileDestination)};
	}

	std::unique_ptr <INotifier> Factory::GetNotifierForFriendRequests(const std::string& username)
	{
		return std::unique_ptr <INotifier>{new Notifier(Factory::GetSystemPathsDefault()->GetFriendRequestsFileDestination(username))};
	}

	std::unique_ptr <INotifier> Factory::GetNotifierForCourseApplicationRequests(const std::string& course)
	{
		return std::unique_ptr <INotifier>{new Notifier(Factory::GetSystemPathsDefault()->GetCourseApplicationRequestsFileDestination(course))};
	}

	std::unique_ptr <IMessageReader> Factory::GetMessageReader(std::unique_ptr<IConversation> conversation)
	{
		return std::unique_ptr <IMessageReader>{new MessageReader(std::move(conversation))};
	}

	std::unique_ptr <IUser> Factory::GetUser(const std::string& username) throw (std::exception)
	{
		return std::unique_ptr <IUser>{std::move(GetSystemApp()->getUser(username))};
	}

	std::shared_ptr <ISystemApp> Factory::GetSystemApp()
	{
		return SystemAppSingleton::GetInstance();
	}
}
