#pragma once

#include <algorithm>
#include <vector>
#include <string>

namespace solid_edu
{
	class CourseStats
	{
	private:
		std::string course1;
		std::string course2;

	public:
		CourseStats(const std::string& course1, const std::string& course2);

		std::string Union();

		std::string Intersection();

		std::string Difference();

	private:
		std::tuple<std::vector<std::string>, std::vector<std::string>>
			sortedStudents();
	};
}
