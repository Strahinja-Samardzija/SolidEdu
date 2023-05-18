#include "StatsWindow.h"
#include "WelcomeWindow.h"
#include "CourseStats.h"
#include "FeatureSelector.h"
#include "Factory.h"

namespace solid_edu
{

	std::unique_ptr<IWindow> StatsWindow::runThenReturnWindow()
	{
		system("cls");

		std::cout << "1. Union of two courses' students" << std::endl;
		std::cout << "2. Intersection of two courses' students" << std::endl;
		std::cout << "3. Difference of two courses' students" << std::endl;
		std::cout << "4. Shortest path through connections graph" << std::endl;
		std::cout << "5. Average distance between users with a feature" << std::endl;

		std::cout << "\n6. Return" << std::endl;


		int option = -1;
		std::cout << "> ";
		std::cin >> option;
		while ((std::cin.fail()))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Error: Please enter an option's number\n";
			std::cout << "> ";
			std::cin >> option;
		}

		if (option >= 1 && option <= 3)
		{
			try
			{
				auto courseA = getCourse(), courseB = getCourse();
				CourseStats temp(courseA, courseB);

				switch (option)
				{
				case 1:
					std::cout << temp.Union() << std::endl;
					break;
				case 2:
					std::cout << temp.Intersection() << std::endl;
					break;
				case 3:
					std::cout << temp.Difference() << std::endl;
					break;
				default:
					break;
				}
			}
			catch (StatsWindow::NotRegistered)
			{
				std::cout << "Press Enter to continue." << std::endl;
				char temp = 0;
				while (temp != '\n')
				{
					std::cin.get(temp);
				}
				return std::unique_ptr<IWindow>{ new StatsWindow()};
			}
		}
		else if (option == 4)
		{
			try
			{
				std::string userA = getUser(), userB = getUser();
				std::cout << Factory::GetSystemApp()->GetConnectionsGraph()->shortestPath(userA, userB) << std::endl;
			}
			catch (StatsWindow::NotRegistered)
			{
				std::cout << "Press Enter to continue." << std::endl;
				char temp = 0;
				while (temp != '\n')
				{
					std::cin.get(temp);
				}
				return std::unique_ptr<IWindow>{ new StatsWindow()};
			}
		}
		else if (option == 5)
		{
			FeatureSelector temp{};
			// todo could do with exceptions
			auto feature = temp.selectFeature();
			auto feature2 = temp.selectFeature();
			if (feature == nullptr || feature2 == nullptr)
			{
				std::cout << "Invalid selection." << std::endl;
				return std::unique_ptr<IWindow>{new WelcomeWindow()};
			}
			std::cout << Factory::GetSystemApp()->GetConnectionsGraph()
				->averageDistanceForFeatures(std::move(feature), std::move(feature2)) << std::endl;
		}
		else if (option == 6)
		{
			return std::unique_ptr<IWindow>{new WelcomeWindow()};
		}

		std::cout << "\n1. Return" << std::endl;

		option = -1;
		std::cout << "> ";
		std::cin >> option;
		while (std::cin.fail() || option != 1)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Error: Please enter an option's number\n";
			std::cout << "> ";
			std::cin >> option;
		}
		return std::unique_ptr<IWindow>{ new StatsWindow()};
	}


	std::string StatsWindow::getUser()
	{
		std::cout << "Username:" << std::endl;
		std::string user;
		std::getline(std::cin >> std::ws, user);
		if (!Factory::GetSystemApp()->isUsernameRegistered(user))
		{
			std::cout << "The user is not registered." << std::endl;
			throw StatsWindow::NotRegistered{};
		}
		return user;
	}

	std::string StatsWindow::getCourse()
	{
		std::cout << "Course:" << std::endl;
		std::string course;
		std::getline(std::cin >> std::ws, course);
		if (!Factory::GetSystemApp()->isCourseRegistered(course))
		{
			std::cout << "The course is not registered." << std::endl;
			throw StatsWindow::NotRegistered{};
		}
		return course;
	}
}
