#include "FilterMessageReader.h"
#include "Factory.h"

namespace solid_edu
{
	FilterMessageReader::FilterMessageReader(const std::string& inboxOwner, const std::string& filter)
		:filteredMessages{}, wrappee{ BasicReader{std::vector<std::string>{}} }
	{
		auto conversations = Factory::GetInbox(inboxOwner)->
			getAllConversations(Factory::GetConnectionsManager()->GetFriends(inboxOwner));

		// filter teachers messages as well
		for (const auto& course : Factory::GetUser(inboxOwner)->getCourses())
		{
			auto teachers = course.GetTeachers();
			std::vector<std::string> teachersVec{};
			auto p = std::copy(teachers.cbegin(), teachers.cend(), std::back_inserter(teachersVec));
			
			auto teachersConversations = Factory::GetInbox(inboxOwner)->getAllConversations(teachersVec);
			for  (auto& conversation : teachersConversations)
			{
				conversations.push_back(std::move(conversation));
			}
		}

		for (auto& conversation : conversations)
		{
			for (const auto& message : conversation->getMessages())
			{
				if (message.substr(message.find_first_of(':') + 1).find(filter) != std::string::npos)
				{
					std::string otherPeer = inboxOwner == conversation->getPeers().first ?
						conversation->getPeers().second : conversation->getPeers().first;
					filteredMessages.push_back("In " + otherPeer + ": " + message);
				}
			}
		}
		wrappee = BasicReader{ filteredMessages };
	}

	void FilterMessageReader::moreMessages()
	{
		wrappee.moreMessages();
	}

	void FilterMessageReader::readMessages()
	{
		wrappee.readMessages();
	}
}
