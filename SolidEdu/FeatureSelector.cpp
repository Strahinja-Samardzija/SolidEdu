#include "FeatureSelector.h"
#include "StudentFeatureExample.h"

namespace solid_edu
{
	std::unique_ptr<solid_edu::IStudentFeature> solid_edu::FeatureSelector::selectFeature() const
	{
		std::cout << "Select a feature" << std::endl;
		std::cout << "1. Username starts with 'm'" << std::endl;
		std::cout << "2. 80% or more of he grades are above 9" << std::endl;

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

		switch (option)
		{
		case 1:
			return std::unique_ptr<solid_edu::IStudentFeature>{new StudentFeatureExample()};
		case 2:
			return std::unique_ptr<solid_edu::IStudentFeature>{new StudentFeatureExample2()};
		default:
			//todo maybe exception or never return non option
			return nullptr;
		}
	}
}