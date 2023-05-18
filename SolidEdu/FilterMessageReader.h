#pragma once
#include <memory>
#include <string>
#include <vector>
#include "IConversation.h"
#include "IMessageReader.h"
#include "BasicReader.h"

namespace solid_edu
{
	//Decorator for BasicReader
	class FilterMessageReader : public IMessageReader
	{
	private:
		BasicReader wrappee;
		std::vector<std::string> filteredMessages;

	public:
		FilterMessageReader(const std::string& username, const std::string& filter);

		void moreMessages() override;
		void readMessages() override;
	};

}

