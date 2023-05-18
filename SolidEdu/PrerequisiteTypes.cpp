#include "PrerequisiteTypes.h"
#include "HardCodedExistingPrerequisiteTypes.h"
#include "Factory.h"

namespace solid_edu
{
	std::unordered_map<std::string, PrerequisiteTypes::Callback> PrerequisiteTypes::constructionTable{};
	std::unordered_map<std::string, std::string> PrerequisiteTypes::serializationTable{};
	std::unordered_map<std::string, std::string> PrerequisiteTypes::argumentSupplyInstructionMessage{};

	void PrerequisiteTypes::InitializeTypes()
	{
		constructionTable = HardCodedExistingTypes::getConstructors();
	}

	std::vector<std::string> PrerequisiteTypes::GetListOfTypeDescriptions()
	{
		std::vector<std::string> descriptions;
		for (auto& key_val : constructionTable)
		{
			descriptions.push_back(key_val.first);
		}
		return descriptions;
	}

	void PrerequisiteTypes::Register(const std::string& concreteDescription, const std::string& serializeString, const std::string& typeDescription, const std::string& argumentSupplyInstruction)
	{
		serializationTable[concreteDescription] = serializeString;
		argumentSupplyInstructionMessage[typeDescription] = argumentSupplyInstruction;
	}

	std::unique_ptr<Prerequisite> PrerequisiteTypes::GetPrerequisite(const std::string& typeDescription, const std::string& args)
	{
		return std::unique_ptr<Prerequisite>{constructionTable[typeDescription](args)};
	}

	std::vector<std::unique_ptr<Prerequisite>> PrerequisiteTypes::GetPrerequisitesForCourse(const std::string& courseName)
	{
		auto prerequisites = std::vector<std::unique_ptr<Prerequisite>>();
		// todo unregistered coursenames tries reading

		std::vector<std::string> lines;
		try
		{
			lines = stringlib::readAllLines(GetCoursePrerequisitesFileDestination(courseName));
		}
		catch (stringlib::bad_filename)
		{
			std::cerr << "Error: Course's prerequisites for course " << courseName << " are currently unavailable.\n";
		}

		for (auto& line : lines)
		{
			std::string type = stringlib::trim(line.substr(0, line.find("-")));
			std::string args = stringlib::trim(line.substr(line.find("-") + 1));
			prerequisites.push_back(std::unique_ptr<Prerequisite>{constructionTable[type](args)});
		}

		return prerequisites;
	}

	void PrerequisiteTypes::MakePrerequisitesForCourse(const std::vector<std::unique_ptr<Prerequisite>>& list, const std::string& courseName)
	{
		std::vector<std::string> lines;
		for (auto& prerequisite : list)
		{
			lines.push_back(serializationTable[prerequisite->GetConcreteDescription()]);
		}

		stringlib::writeAllLines(GetCoursePrerequisitesFileDestination(courseName), lines);
	}

	std::string PrerequisiteTypes::ArgumentSupplyInstruction(const std::string& typeDescription)
	{
		return argumentSupplyInstructionMessage[typeDescription];
	}

	void PrerequisiteTypes::RegisterCourseSubscription(const std::string& courseName)
	{
		try
		{
			stringlib::createFile(GetCoursePrerequisitesFileDestination(courseName));
		}
		catch (const stringlib::bad_filename& e)
		{
			std::cerr << "Error: Cannot register course's prerequisites";
		}
	}

	void PrerequisiteTypes::DeleteCourseSubscription(const std::string& courseName)
	{
		try
		{
			stringlib::deleteFile(GetCoursePrerequisitesFileDestination(courseName).c_str());
		}
		catch (const stringlib::bad_filename& e)
		{
			std::cerr << "Error: Course's subscription data for course " << courseName << " is unavailable.\n";
		}
	}

	std::string PrerequisiteTypes::GetCoursePrerequisitesFileDestination(const std::string& courseName)
	{
		//todo no point in making it specialized when it should be uniform
		return Factory::GetSystemPathsDefault()->courseObjectPath + courseName + "_prerequisites.txt";
	}
}
