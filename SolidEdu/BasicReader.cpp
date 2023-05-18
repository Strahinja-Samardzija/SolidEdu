#include "BasicReader.h"
#include <iostream>

namespace solid_edu
{
	BasicReader::BasicReader(const std::vector<std::string>& messages)
		: messages{ messages } {}

	void solid_edu::BasicReader::readMessages()
	{
		indexUnread = READ_COUNT;
		moreMessages();
	}

	void solid_edu::BasicReader::moreMessages()
	{
		for (int i = 1; i <= READ_COUNT && indexUnread > 0; indexUnread--, i++)
		{
			if (indexUnread > messages.size())
			{
				continue;
			}
			std::cout << messages[messages.size() - indexUnread] << '\n';
		}
		indexUnread += 2 * READ_COUNT;
	}
}
