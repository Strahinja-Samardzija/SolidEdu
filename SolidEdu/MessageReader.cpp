#include "MessageReader.h"

namespace solid_edu
{

	MessageReader::MessageReader(std::unique_ptr<IConversation> conversation) 
		: peers{ conversation->getPeers() }, messages{ conversation->getMessages() }, wrappee{ BasicReader{std::vector<std::string>{}} }
	{
		wrappee = BasicReader{ messages };
	}

	void MessageReader::readMessages()
	{
		// allows reset - messages are again read starting from the most recent one
		std::cout << "Conversation between " << peers.first << " and " << peers.second << " :\n" ;
		wrappee.readMessages();
	}

	void MessageReader::moreMessages()
	{
		wrappee.moreMessages();
	}
}
