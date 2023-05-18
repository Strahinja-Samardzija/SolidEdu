#pragma once

#include "IConversation.h"
#include "Factory.h"
#include "StringLib.h"
#include <string>
#include <vector>

namespace solid_edu
{
	class Conversation : public IConversation
	{
	private:
		std::pair<std::string, std::string> peers;

		// these are trimmed messages
		std::vector<std::string> messages;
		std::string conversationFileDestination;

		Conversation(const std::string& peer1, const std::string& peer2, std::vector<std::string>& messages, const std::string& conversationFileDestination);

		Conversation(const Conversation& other);

		~Conversation() = default;

	public:
		Conversation* clone() override;

	public:
		// static method for Factory to call
		static Conversation* GetConversation(const std::string& conversationFileDestination);

		void writeMessage(const std::string& sender, const std::string& message);

		std::vector<std::string> getMessages() const override;

		std::pair<std::string, std::string> getPeers() const override;
	};
}
