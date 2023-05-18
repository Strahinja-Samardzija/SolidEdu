#pragma once

#include "Prerequisite.h"
#include "StringLib.h"
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <functional>

//todo constructor table and string helper functions
namespace solid_edu
{
	class PrerequisiteTypes 
	{
	public:
		using Callback = std::function<Prerequisite*(const std::string&)>;

	private:
		static std::unordered_map<std::string, Callback> constructionTable;
		static std::unordered_map<std::string, std::string> serializationTable;
		static std::unordered_map<std::string, std::string> argumentSupplyInstructionMessage;

	public:
		static void InitializeTypes();

		static std::vector<std::string> GetListOfTypeDescriptions();

		static void Register(
			const std::string& concreteDescription,
			const std::string& serializeString,
			const std::string& typeDescription,
			const std::string& argumentSupplyInstruction);

		static std::unique_ptr<Prerequisite> GetPrerequisite(
			const std::string& typeDescription, const std::string& args);

		static std::vector<std::unique_ptr<Prerequisite>> 
			GetPrerequisitesForCourse(const std::string& courseName);

		static void MakePrerequisitesForCourse(
			const std::vector<std::unique_ptr<Prerequisite>>& list, 
			const std::string& courseName);

		static std::string ArgumentSupplyInstruction(const std::string& typeDescription);

		static void RegisterCourseSubscription(const std::string& courseName);

		static void DeleteCourseSubscription(const std::string& courseName);

	private:
		static std::string GetCoursePrerequisitesFileDestination(const std::string& courseName);
	};
}
