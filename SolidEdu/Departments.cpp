#include "Departments.h"

namespace solid_edu
{

	std::string Departments::departmentsFileDestination = "departments.txt";
	std::unordered_map<std::string, std::unordered_set<std::string>> Departments::departmentToCourses;

	void Departments::InitalizeDepartments()
	{
		std::vector<std::string> lines = stringlib::readAllLines(departmentsFileDestination);
		//todo for every lines.Length == 0, check if exception needed, and also check if initializing sets to new empty

		for (auto& line : lines)
		{
			std::string department = stringlib::trim(line.substr(0, line.find("-")));
			if (stringlib::endsWith(line, "- "))
			{
				departmentToCourses[department] = std::unordered_set<std::string>();
				continue;
			}

			departmentToCourses[department] = std::unordered_set<std::string>();
			std::vector<std::string> rest = stringlib::split(line.substr(line.find("-") + 1), ',');
			for (auto& course : rest)
			{
				departmentToCourses[department].insert(course);
			}
		}
	}

	bool Departments::isDepartmentRegistered(const std::string& department)
	{
		return departmentToCourses.find(department) != departmentToCourses.end();
	}

	void Departments::RegisterDepartment(const std::string& departmentName, const std::vector<std::string>& courses)
	{
		std::string newLine = departmentName + " - ";
		for (auto& course : courses)
		{
			newLine += course + ", ";
		}
		newLine.erase(newLine.length() - 2);

		stringlib::appendAllLines(departmentsFileDestination, std::vector<std::string> {newLine});

		departmentToCourses[departmentName] = std::unordered_set<std::string>{};
		std::copy(courses.cbegin(), courses.cend(),
			std::inserter(departmentToCourses.at(departmentName), departmentToCourses.at(departmentName).begin()));
	}

	void Departments::removeDepartment(const std::string& department)
	{
		std::vector<std::string> lines = stringlib::readAllLines(departmentsFileDestination);

		auto p = std::remove_if(lines.begin(), lines.end(),
			[&department](auto& line)
			{
				return stringlib::startsWith(line, department);
			}
		);
		if (p != lines.end())
			lines.erase(p, lines.end());

		stringlib::writeAllLines(departmentsFileDestination, lines);

		departmentToCourses.erase(department);
	}

	void Departments::AddCourseToDepartment(const std::string& courseName, const std::string& department)
	{
		if (departmentToCourses.find(department) == departmentToCourses.end())
		{
			std::cout << "No such department" << std::endl;
			return;
		}

		std::vector<std::string> lines = stringlib::readAllLines(departmentsFileDestination);

		for (int i = 0; i < lines.size(); i++)
		{
			std::string departmentRead = stringlib::trim(lines[i].substr(0, lines[i].find("-")));
			if (department == departmentRead)
			{
				departmentToCourses[department].insert(courseName);
				if (stringlib::endsWith(lines[i], "- "))
				{
					lines[i] += courseName;
				}
				else
				{
					lines[i] += ", " + courseName;
				}
			}
		}

		stringlib::writeAllLines(departmentsFileDestination, lines);
	}

	std::string Departments::departmentOf(const std::string& courseName)
	{
		for (auto& key : departmentToCourses)
		{
			if (std::find(departmentToCourses[key.first].begin(), departmentToCourses[key.first].end(), courseName) != departmentToCourses[key.first].end())
			{
				return key.first;
			}
		}
		return "";
	}

	void Departments::RemoveCourseFromDepartment(const std::string& courseName, const std::string& department)
	{
		std::vector<std::string> lines = stringlib::readAllLines(departmentsFileDestination);

		for (int i = 0; i < lines.size(); i++)
		{
			std::string departmentRead = stringlib::trim(lines[i].substr(0, (int)lines[i].find("-")));
			if (department == departmentRead)
			{
				lines[i] = lines[i].substr(0, lines[i].find(", " + courseName))
					+ lines[i].substr((int)lines[i].find(courseName)
						+ courseName.size());
			}
		}
		stringlib::writeAllLines(departmentsFileDestination, lines);

		departmentToCourses[department].erase(courseName);
	}
}
