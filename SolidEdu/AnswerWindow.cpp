#include "AnswerWindow.h"
#include "UserMenuWindow.h"
#include "ConversationWindow.h"
#include <algorithm>

namespace solid_edu
{
	AnswerWindow::AnswerWindow(std::vector<std::string>& peers, std::unique_ptr<IUser> user)
		: peers{ peers }, user{ std::move(user) } {}

	std::unique_ptr<IWindow> AnswerWindow::runThenReturnWindow()
	{
		std::vector<std::string> teacherList{};
		std::vector<std::string> nonTeacherPeers{};

		int counter{};
		for (auto& course : user->getCourses())
		{
			auto returnedTeachers = course.GetTeachers();
			for (auto& peer : peers)
			{
				if (returnedTeachers.find(peer) != returnedTeachers.cend())
				{
					counter++;
					std::cout << counter << ". " << course << " teacher: " << peer << '\n';

					teacherList.push_back(peer);
				}
			}
		}

		std::copy_if(peers.cbegin(), peers.cend(), std::back_inserter(nonTeacherPeers),
			[&teacherList](auto& peer)
			{
				return std::find(teacherList.cbegin(), teacherList.cend(), peer) != teacherList.cend();
			});

		for (auto& peer : nonTeacherPeers)
		{
			counter++;
			std::cout << counter << ". " << peer << '\n';
		}

		std::cout << '\n' << (counter + 1) << ". " << "Return to menu" << '\n';

		int option = -1;
		std::cout << "> ";
		std::cin >> option;
		while (std::cin.fail() || option > counter + 1 || option <= 0)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Error: Please enter an option's number\n";
			std::cout << "> ";
		}

		int limes = teacherList.size();
		if (option == counter + 1)
		{
			return std::unique_ptr<IWindow>{new UserMenuWindow(std::unique_ptr<IUser>{user->clone()})};
		}
		if (option <= limes)
		{
			ConversationWindow temp(teacherList[option - 1], std::unique_ptr<IUser>(user->clone()));
			temp.runThenReturnWindow(); // ignore returned window
			return std::unique_ptr<IWindow>{new AnswerWindow(peers, std::unique_ptr<IUser>{user->clone()})};
		}
		else
		{
			ConversationWindow temp(nonTeacherPeers[option - (limes + 1)], std::unique_ptr<IUser>(user->clone()));
			temp.runThenReturnWindow(); // ignore returned window
			return std::unique_ptr<IWindow>{new AnswerWindow(peers, std::unique_ptr<IUser>{user->clone()})};
		}
	}
}
