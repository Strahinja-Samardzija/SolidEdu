#pragma once

#include <string>
#include <vector>

namespace solid_edu
{
	class IConversation
	{
	public:
		virtual void writeMessage(const std::string& sender, const std::string& message) = 0;
		virtual std::vector<std::string> getMessages() const = 0;
		virtual std::pair<std::string, std::string> getPeers() const = 0;

		//todo make every cclone const
		virtual IConversation* clone() = 0;
		virtual ~IConversation() = 0 {};
	};
}
