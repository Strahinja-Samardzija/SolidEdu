#include "CourseStats.h"
#include "Course.h"
#include "StringLib.h"

namespace solid_edu
{
	CourseStats::CourseStats(const std::string& course1, const std::string& course2)
		: course1{ course1 }, course2{ course2 } {}

	std::string CourseStats::Union()
	{
		std::vector<std::string> sorted1{}, sorted2{}, unionVec{};
		std::tie(sorted1, sorted2) = sortedStudents();

		std::set_union(sorted1.cbegin(), sorted1.cend(), sorted2.cbegin(), sorted2.cend(),
			std::back_inserter(unionVec));
		return stringlib::prettyPrint<std::vector<std::string>>(unionVec);
	}

	std::string CourseStats::Intersection()
	{
		std::vector<std::string> sorted1{}, sorted2{}, intersectionVec{};
		std::tie(sorted1, sorted2) = sortedStudents();

		std::set_intersection(sorted1.cbegin(), sorted1.cend(), sorted2.cbegin(), sorted2.cend(),
			std::back_inserter(intersectionVec));
		return stringlib::prettyPrint<std::vector<std::string>>(intersectionVec);
	}

	std::string CourseStats::Difference()
	{
		std::vector<std::string> sorted1{}, sorted2{}, differenceVec{};
		std::tie(sorted1, sorted2) = sortedStudents();

		std::set_difference(sorted1.cbegin(), sorted1.cend(), sorted2.cbegin(), sorted2.cend(),
			std::back_inserter(differenceVec));
		return stringlib::prettyPrint<std::vector<std::string>>(differenceVec);
	}

	std::tuple<std::vector<std::string>, std::vector<std::string>> CourseStats::sortedStudents()
	{
		Course tempCourse1{ course1 };
		auto courseStudents1 = tempCourse1.GetStudents();
		Course tempCourse2{ course2 };
		auto courseStudents2 = tempCourse2.GetStudents();
		std::vector<std::string> sorted1(courseStudents1.size());
		std::vector<std::string> sorted2(courseStudents2.size());

		std::partial_sort_copy(courseStudents1.cbegin(), courseStudents1.cend(),
			sorted1.begin(), sorted1.end());
		std::partial_sort_copy(courseStudents2.cbegin(), courseStudents2.cend(),
			sorted2.begin(), sorted2.end());

		return std::forward_as_tuple(sorted1, sorted2);
	}
}
