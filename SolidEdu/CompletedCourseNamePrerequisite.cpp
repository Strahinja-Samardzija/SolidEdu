#include "CompletedCourseNamePrerequisite.h"
#include "Factory.h"

namespace solid_edu
{
	CompletedCourseNamePrerequisite::CompletedCourseNamePrerequisite(const std::string& courseName)
	{
		this->courseName = courseName;
		PrerequisiteTypes::Register(GetConcreteDescription(), getSerializeString(courseName), GetTypeDescription(), SupplyArgsInstruction());
	}

	Prerequisite* CompletedCourseNamePrerequisite::clone() const
	{
		return new_object(courseName);
	}

	CompletedCourseNamePrerequisite* CompletedCourseNamePrerequisite::new_object(const std::string& courseName)
	{
		return new CompletedCourseNamePrerequisite(courseName);
	}

	void CompletedCourseNamePrerequisite::failMassage() const
	{
		std::cout << "You have to complete the " << courseName << " course first.\n";
		system("pause");
	}

	std::string CompletedCourseNamePrerequisite::GetConcreteDescription() const
	{
		return "completed course: " + courseName;
	}

	std::string CompletedCourseNamePrerequisite::GetTypeDescription() const
	{
		return "completed a particular course";
	}

	bool CompletedCourseNamePrerequisite::metBy(const std::string& username) const
	{
		// todo check for std::move
		std::unique_ptr<StudentDecorator> temp{ new StudentDecorator{Factory::GetSystemApp()->getUser(username)} };
		return temp->hasCompletedCourse(courseName);
	}

	std::string CompletedCourseNamePrerequisite::getSerializeString(const std::string& args) const
	{
		return GetTypeDescription() + " - " + courseName;
	}

	std::string CompletedCourseNamePrerequisite::SupplyArgsInstruction() const
	{
		return "Enter course name:";
	}
}
