#pragma once

#include "BasicReader.h"
#include "IMessageReader.h"
#include "Factory.h"
#include "IConversation.h"
#include <string>
#include <vector>
#include <iostream>
#include <memory>

namespace solid_edu
{
	//Decorator for BasicReader
	class MessageReader : public IMessageReader
	{
	private:
		BasicReader wrappee;
		std::pair<std::string, std::string> peers;
		std::vector<std::string> messages;

	public:
		MessageReader(std::unique_ptr<IConversation> conversation);

		void readMessages() override;

		void moreMessages() override;
	};
}
