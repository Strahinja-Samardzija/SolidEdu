#include "CoursePrerequisiteModifier.h"

namespace solid_edu
{
	CoursePrerequisiteModifier::CoursePrerequisiteModifier(const Course& course)
		: course{ course } {}

	void CoursePrerequisiteModifier::RemovePrerequisite()
	{
		auto listOfPrerequisites = course.getPrerequisites();
		int i = 1;
		for (auto& prerequisite : listOfPrerequisites)
		{
			std::cout << "" << i++ << ". " << prerequisite->GetConcreteDescription() << std::endl;
		}

		int option = -1;
		std::cout << "> ";
		std::cin >> option;
		while ((std::cin.fail()) || option <= 0 || option >= i)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Error: Please enter an option's number\n";
			std::cout << "> ";
			std::cin >> option;
		}

		course.RemovePrerequisite(*listOfPrerequisites[option - 1]);
	}

	void CoursePrerequisiteModifier::AddPrerequisite()
	{
		auto listOfTypeDescriptionStrings = PrerequisiteTypes::GetListOfTypeDescriptions();

		int i = 1;
		for (auto& type : listOfTypeDescriptionStrings)
		{
			std::cout << "" << i++ << ". " << type << std::endl;
		}

		int option = -1;
		std::cout << "> ";
		std::cin >> option;
		while ((std::cin.fail()) || option <= 0 || option >= i)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Error: Please enter an option's number\n";
			std::cout << "> ";
			std::cin >> option;
		}
		
		std::cout << PrerequisiteTypes::ArgumentSupplyInstruction(listOfTypeDescriptionStrings[option - 1]) << std::endl;
		std::string args;
		std::getline(std::cin >> std::ws, args);
		auto prerequisite = PrerequisiteTypes::GetPrerequisite(listOfTypeDescriptionStrings[option - 1], args);
		course.NewPrerequisite(*prerequisite);
	}
}
