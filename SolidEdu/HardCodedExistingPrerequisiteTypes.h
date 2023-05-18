#pragma once

#include "PrerequisiteTypes.h"
#include "CompletedCourseNamePrerequisite.h"
#include <string>
#include <unordered_map>
#include <functional>

namespace solid_edu
{
	class HardCodedExistingTypes 
	{
	private:
		static std::unordered_map<std::string, PrerequisiteTypes::Callback> constructionTable;

	public:
		static std::unordered_map<std::string, PrerequisiteTypes::Callback> getConstructors()
		{
			// repeat for every new type of prerequisite
			constructionTable["completed a particular course"] =
				&CompletedCourseNamePrerequisite::new_object;

			return constructionTable;
		};
	};
}
