#include "MeetPeopleWindow.h"
#include "UserMenuWindow.h"
#include "Notifier.h"

#include <random>

namespace solid_edu
{

	MeetPeopleWindow::MeetPeopleWindow(std::unique_ptr<IUser> user)
		:user{ std::move(user) } {}

	std::unique_ptr<IWindow> MeetPeopleWindow::runThenReturnWindow()
	{
		// people you may know are friends of your friends and students of courses you attend
		auto peopleYouMayKnow = GetPeopleYouMayKnow();
		int counter = 0;

		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		std::uniform_int_distribution<> random(0, peopleYouMayKnow.size() - 1);
		std::vector<std::string> peoplePickedRandomly;

		std::cout << "People you may know:" << '\n';
		for (int i = 0; i < 5; i++)
		{
			int randomIndex{ random(gen) };
			std::string person = peopleYouMayKnow[randomIndex];
			if (std::find(peoplePickedRandomly.begin(), peoplePickedRandomly.end(), person)
				== peoplePickedRandomly.end() && person != user->getUsername())
			{
				counter++;
				std::cout << counter << ". " << peopleYouMayKnow[randomIndex] << '\n';

				peoplePickedRandomly.push_back(person);
			}
		}

		int limes = counter;
		counter++;
		std::cout << "\n" << counter << ". " << "Search: " << '\n';

		std::cout << "\n" << (counter + 1) << ". " << "Return to menu" << '\n';

		int option = -1;
		std::cout << "> ";
		std::cin >> option;
		while ((std::cin.fail()) || option > counter + 1 || option <= 0)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Error: Please enter an option's number\n";
			std::cout << "> ";
			std::cin >> option;
		}

		if (option == counter + 1)
		{
			return std::unique_ptr<IWindow>{new UserMenuWindow(std::unique_ptr<IUser>{user->clone()})};
		}
		if (option <= limes)
		{
			Notifier tempVar(Factory::GetSystemPathsDefault()->GetFriendRequestsFileDestination(peoplePickedRandomly[option - 1]));
			(&tempVar)->notify(user->getUsername());

			return std::unique_ptr<IWindow>{new UserMenuWindow(std::unique_ptr<IUser>{user->clone()})};
		}
		else
		{
			std::cout << "Username:" << '\n';
			std::string newFriend;
			std::getline(std::cin >> std::ws, newFriend);
			if (!Factory::GetSystemApp()->isUsernameRegistered(newFriend))
			{
				std::cout << "This user is not registered. Returning to Menu." << '\n';
				system("pause");
				return std::unique_ptr<IWindow>{new UserMenuWindow(std::unique_ptr<IUser>{user->clone()})};
			}

			Factory::GetNotifierForFriendRequests(newFriend)
				->notify(user->getUsername());

			return std::unique_ptr<IWindow>{new UserMenuWindow(std::unique_ptr<IUser>{user->clone()})};
		}
	}

	std::vector<std::string> MeetPeopleWindow::GetPeopleYouMayKnow()
	{
		auto yourFriends = Factory::GetConnectionsManager()
			->GetFriends(user->getUsername());

		// contains friends of your friends and all your classmates
		std::unordered_set<std::string> peopleYouMayKnow{};

		for (auto& yourFriend : yourFriends)
		{
			auto hisFriends =
				Factory::GetConnectionsManager()->GetFriends(yourFriend);

			std::copy_if(hisFriends.cbegin(), hisFriends.cend(),
				std::inserter(peopleYouMayKnow, peopleYouMayKnow.begin()),
				[&yourFriends](auto& hisFriend)
				{
					return std::find(yourFriends.cbegin(), yourFriends.cend(), hisFriend)
						== yourFriends.cend();
				}
			);
		}

		for (auto& course : user->getCourses())
		{
			auto courseStudents = course.GetStudents();
			for (auto& classmate : courseStudents)
			{
				peopleYouMayKnow.insert(classmate);
			}
		}

		std::vector<std::string> toVector{};
		std::copy(peopleYouMayKnow.cbegin(), peopleYouMayKnow.cend(), std::back_inserter(toVector));
		return toVector;
	}
}
