#include "Conversation.h"

namespace solid_edu
{

	Conversation::Conversation(
		const std::string& peer1, 
		const std::string& peer2, 
		std::vector<std::string>& messages,
		const std::string& conversationFileDestination
	)
		: peers{std::make_pair(peer1, peer2)},
		messages{messages},
		conversationFileDestination{conversationFileDestination} {}

	Conversation::Conversation(const Conversation& other) :
		peers{ other.peers },
		messages{ other.messages },
		conversationFileDestination{ other.conversationFileDestination } {}

	Conversation* Conversation::clone()
	{
		return new Conversation(*this);
	}

	Conversation* Conversation::GetConversation(const std::string& conversationFileDestination)
	{
		auto peers = stringlib::split(conversationFileDestination.substr(conversationFileDestination.rfind("\\") + 1), '_');

		if (!stringlib::fileExists(conversationFileDestination))
		{
			stringlib::createFile(conversationFileDestination);
		}

		auto messages = stringlib::readAllLines(conversationFileDestination, '~');;

		for (int i = 0; i < messages.size(); i++)
		{
			messages[i] = stringlib::trim(messages[i]);
		}

		return new Conversation(peers[0], peers[1], messages, conversationFileDestination);
	}

	void Conversation::writeMessage(const std::string& sender, const std::string& message)
	{
		auto& receiver = sender == peers.first ? peers.second : peers.first;

		try
		{
			Factory::GetSystemApp()->getUser(receiver)->getInbox()->notify(sender);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what();
		}
		stringlib::appendAllLines(conversationFileDestination, std::vector<std::string> {"~" + sender + 
			": " + stringlib::trim(message)});
	}

	std::vector<std::string> Conversation::getMessages() const
	{
		return messages;
	}

	std::pair<std::string, std::string> Conversation::getPeers() const
	{
		return peers;
	}
}
