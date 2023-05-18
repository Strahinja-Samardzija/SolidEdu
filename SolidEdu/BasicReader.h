#pragma once
#include "IMessageReader.h"
#include <vector>
#include <string>

namespace solid_edu
{
	class BasicReader : public IMessageReader
	{
	public:
		enum {READ_COUNT = 13};
	private:
		int indexUnread{};
		std::vector<std::string> messages;
	
	public:
		BasicReader(const std::vector<std::string>& messages);

		// Inherited via IMessageReader
		virtual void readMessages() override;

		// Inherited via IMessageReader
		virtual void moreMessages() override;
	};

}

