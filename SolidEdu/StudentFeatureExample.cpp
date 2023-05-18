#include "StudentFeatureExample.h"
#include "StudentDecorator.h"
#include "User.h"
#include "Factory.h"

namespace solid_edu
{
	bool solid_edu::StudentFeatureExample::hasFeature(const std::string& username) const
	{
		return stringlib::startsWith(username, "m");
	}
	bool StudentFeatureExample2::hasFeature(const std::string& username) const
	{
		StudentDecorator student{ std::unique_ptr<IUser>{Factory::GetUser(username)}};
		auto grades = student.getAllGrades();

		int count9and10 = std::count_if(grades.cbegin(), grades.cend(), 
			[](const std::tuple<std::string, int>& tuple) {return (std::get<1>(tuple)) >= 9; });
		if (count9and10 > grades.size() / 1.25) {
			return true;
		}
		return false;
	}
}
