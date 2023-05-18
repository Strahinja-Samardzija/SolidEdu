#pragma once

#include "Prerequisite.h"
#include <ostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <memory>

namespace solid_edu
{
	class Course;
	using Course_HashSet = std::unordered_set<Course, std::hash<Course>, std::equal_to<Course>>;

	class Course
	{
	private:
		std::string courseName;

		std::unordered_set<std::string> teachers{};
		std::unordered_set<std::string> students{};
		std::vector<std::unique_ptr<Prerequisite>> prerequisites{};

	public:
		Course(const std::string& courseName);

		Course(const Course& other);
		Course& operator=(const Course& other);

		Course(Course&& other) noexcept;
		Course& operator=(Course&& other) noexcept;

		~Course() = default;

		friend std::ostream& operator<<(std::ostream& os, const Course& course);

	private:
		void initializePrerequisites();

		void initializeTeachers();

		void initializeStudents();

	public:
		std::unordered_set<std::string> GetTeachers() const;

		std::unordered_set<std::string> GetStudents() const;

		std::vector<std::unique_ptr<Prerequisite>> getPrerequisites() const;

		void RegisterStudent(const std::string& student);

		void RegisterTeacher(const std::string& teacher);

		void RemoveStudent(const std::string& student);

		void RemoveTeacher(const std::string& teacher);

		void RemoveSelf();

		void NewPrerequisite(const Prerequisite& prerequisite);

		void RemovePrerequisite(const Prerequisite& prerequisite);

		std::string getCourseTitle() const;

		bool hasStudent(const std::string& username) const;

		bool hasTeacher(const std::string& username) const;

		void ApplyForRegistration(const std::string& username);

	private:
		bool meetsPrerequisites(const std::string& username) const;
	};

	inline std::ostream& operator<<(std::ostream& os, const Course& course)
	{
		os << course.courseName;
		return os;
	}
}

namespace std
{
	template <> struct hash<solid_edu::Course>
	{
		size_t operator()(const solid_edu::Course& x) const
		{
			return hash<string>()(x.getCourseTitle());
		}
	};

	template <> struct equal_to<solid_edu::Course>
	{
		bool operator()(const solid_edu::Course& c1, const solid_edu::Course& c2) const
		{
			return c1.getCourseTitle() == c2.getCourseTitle();
		}
	};
}