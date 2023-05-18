#pragma once

#include "ConnectionsGraph.h"

#include "IConnectionsManager.h"
#include "solid_edu_IStudentFeature.h"
#include "solid_edu_IConnectionsGraph.h"
#include "IFeatureSelector.h"
#include "ICourseFileManager.h"
#include "ICompletedCoursesFileManager.h"
#include "ICompletedCoursesFileManager.h"
#include "IUser.h"
#include "IMessageReader.h"
#include "IConversation.h"
#include "IInbox.h"
#include "INotifier.h"
#include "ISystemApp.h"
#include "SystemPathsBase.h"

#include <string>
#include <memory>

namespace solid_edu
{
	static class Factory
	{
		//todo make static library connectionsgraph only c++
	public:
		static std::unique_ptr<IInbox> GetInbox(const std::string& user);

		static std::unique_ptr<ICourseFileManager> GetCourseFileManager();

		static std::unique_ptr<ICompletedCoursesFileManager> GetCompletedCoursesFileManager();


		static std::unique_ptr<IFeatureSelector>GetFeatureSelector();

		static std::shared_ptr<solid_edu::IConnectionsGraph> GetConnectionsGraph(const std::string& fileDestination);

		//todo
		static std::shared_ptr<SystemPathsBase> GetSystemPathsFromFile(const std::string& fileDestination);

		static std::shared_ptr<SystemPathsBase> GetSystemPathsDefault();

		static std::shared_ptr<IConnectionsManager> GetConnectionsManager();

		static std::unique_ptr<IConversation> GetConversation(const std::string& conversationFileDestination);

		static std::unique_ptr<INotifier> getNotifierForFileStorageInbox(const std::string& notificationsFileDestination);

		static std::unique_ptr<INotifier> GetNotifierForFriendRequests(const std::string& username);

		static std::unique_ptr<INotifier> GetNotifierForCourseApplicationRequests(const std::string& course);

		static std::unique_ptr<IMessageReader> GetMessageReader(std::unique_ptr<IConversation> conversation);

		static std::unique_ptr<IUser> GetUser(const std::string& username);

		static std::shared_ptr<ISystemApp> GetSystemApp();
	};
}
