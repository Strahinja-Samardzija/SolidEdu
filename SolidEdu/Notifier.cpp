#include "Notifier.h"
#include "StringLib.h"

namespace solid_edu
{

	Notifier::Notifier(const std::string& notificationsFileDestination) : notificationsFileDestination{ notificationsFileDestination } {}

	void Notifier::notify(const std::string& senderUsername)
	{
		auto originalLines{ stringlib::readAllLines(notificationsFileDestination) };
		if (originalLines.empty())
		{
			stringlib::writeAllLines(notificationsFileDestination, std::vector<std::string> {"1 new message", senderUsername});
			return;
		}

		std::ostringstream changedFirstLine = std::ostringstream{};
		changedFirstLine
			<< 1 + std::stoi(originalLines[0].substr(0, originalLines[0].find(' ')))
			<< " new messages";
		if (std::find_if(originalLines.cbegin(), originalLines.cend(),
			[&senderUsername](auto line) {return line == senderUsername; })
			== originalLines.cend())
		{
			originalLines.push_back(senderUsername);
		}
		originalLines[0] = changedFirstLine.str();
		stringlib::writeAllLines(notificationsFileDestination, originalLines);
	}

	std::string Notifier::getNotificationsBadge()
	{
		auto notifications{ stringlib::readAllLines(notificationsFileDestination) };
		if (notifications.size() != 0)
		{
			return notifications[0];
		}
		else
		{
			return "";
		}
	}

	std::vector<std::string> Notifier::getNotificationsPeers()
	{
		std::vector<std::string> peers;
		auto lines{ stringlib::readAllLines(notificationsFileDestination) };
		if (lines.empty())
		{
			return std::vector<std::string>();
		}

		for (auto& line : lines)
		{
			if (line.find("new message") == std::string::npos)
				peers.push_back(line);
		}

		// delete text
		stringlib::writeAllLines(notificationsFileDestination, std::vector<std::string>{});

		return peers;
	}

	void Notifier::RegisterCourseSubscription()
	{
		stringlib::createFile(notificationsFileDestination);
	}

	void Notifier::DeleteCourseSubscription()
	{
		try
		{
			stringlib::deleteFile(notificationsFileDestination);
		}
		catch (stringlib::bad_filename)
		{
			std::cerr << "Error: Subscription details (Notifier) for course: "
				<< notificationsFileDestination.substr(0, notificationsFileDestination.rfind('_'))
				<< " are currently unavailable.\n";
		}
	}

	void Notifier::RegisterUsersFriendRequestSubscription()
	{
		stringlib::createFile(notificationsFileDestination);
	}

	void Notifier::DeleteUsersFriendRequestSubscription()
	{
		try
		{
			stringlib::deleteFile(notificationsFileDestination);
		}
		catch (stringlib::bad_filename)
		{
			std::cerr << "Error: Subscription details (Notifier) for user: "
				<< notificationsFileDestination.substr(notificationsFileDestination.rfind("\\" + 1), notificationsFileDestination.find('_'))
				<< " are currently unavailable.\n";
		}
	}
}
