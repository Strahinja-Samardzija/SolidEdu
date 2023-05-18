#pragma once
#include "Prerequisite.h"
#include "PrerequisiteTypes.h"
#include "StudentDecorator.h"

#include <string>
#include <iostream>

namespace solid_edu
{
	class CompletedCourseNamePrerequisite : public Prerequisite
	{
	private:
		std::string courseName;

	public:
		CompletedCourseNamePrerequisite(const std::string& courseName);

		Prerequisite* clone() const override;

		static CompletedCourseNamePrerequisite* new_object(const std::string& courseName);

	public:
		inline void failMassage() const override;

		inline std::string GetConcreteDescription() const override;

		inline std::string GetTypeDescription() const override;

		bool metBy(const std::string& username) const override;

		inline std::string SupplyArgsInstruction() const override;

	private:
		inline std::string getSerializeString(const std::string& args) const;

	};
}
