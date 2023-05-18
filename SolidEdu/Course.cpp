#include "Factory.h"
#include "Course.h"
#include "Departments.h"
#include "PrerequisiteTypes.h"

namespace solid_edu
{
	Course::Course(const std::string& courseName)
	{
		this->courseName = courseName;
		initializeStudents();
		initializeTeachers();
		initializePrerequisites();
	}

	Course::Course(const Course& other)
		: courseName{ other.courseName },
		teachers{ other.teachers },
		students{ other.students },
		prerequisites{}
	{
		for (auto& prerequisite : other.prerequisites)
		{
			prerequisites.emplace_back(prerequisite->clone());
		}
	}

	Course& Course::operator=(const Course& other)
	{
		if (this != &other)
		{
			this->courseName = other.courseName;
			this->teachers = other.teachers;
			this->students = other.students;
			this->prerequisites = std::vector<std::unique_ptr<Prerequisite>>{};

			for (auto& prerequisite : other.prerequisites)
			{
				this->prerequisites.emplace_back(prerequisite->clone());
			}
		}
		return *this;
	}

	Course::Course(Course&& other) noexcept
		: courseName{},
		teachers{},
		students{},
		prerequisites{}
	{
		*this = std::move(other);
	}

	Course& Course::operator=(Course&& other) noexcept
	{
		if (this != &other)
		{
			this->courseName = other.courseName;
			this->teachers = std::move(other.teachers);
			this->students = std::move(other.students);
			this->prerequisites = std::move(other.prerequisites);
		}
		return *this;
	}

	void Course::initializePrerequisites()
	{
		prerequisites = PrerequisiteTypes::GetPrerequisitesForCourse(courseName);
	}

	void Course::initializeTeachers()
	{
		teachers = Factory::GetCourseFileManager()->ReadTeachersForCourse(courseName);
	}

	void Course::initializeStudents()
	{
		students = Factory::GetCourseFileManager()->ReadStudentsForCourse(courseName);
	}

	std::unordered_set<std::string> Course::GetTeachers() const
	{
		return teachers;
	}

	std::unordered_set<std::string> Course::GetStudents() const
	{
		return students;
	}

	std::vector<std::unique_ptr<Prerequisite>> Course::getPrerequisites() const
	{
		decltype(getPrerequisites()) toReturn{};
		for (auto& prerequisite : prerequisites)
		{
			toReturn.emplace_back(prerequisite->clone());
		}
		return toReturn;
	}

	void Course::RegisterStudent(const std::string& student)
	{
		students.insert(student);
		Factory::GetCourseFileManager()->RegisterCourseInUsersLocalFile(courseName, student);
		Factory::GetCourseFileManager()->RegisterStudentToCourseInGlobalFile(student, courseName);
	}

	void Course::RegisterTeacher(const std::string& teacher)
	{
		teachers.insert(teacher);
		Factory::GetCourseFileManager()->RegisterCourseInUsersLocalFile(courseName, teacher);
		Factory::GetCourseFileManager()->RegisterTeacherToCourseInGlobalFile(teacher, courseName);
	}

	void Course::RemoveStudent(const std::string& student)
	{
		students.erase(student);
		Factory::GetCourseFileManager()->RemoveStudentFromCoursesInGlobalFile(student, std::vector<std::string> {courseName});
		Factory::GetCourseFileManager()->RemoveCoursesFromUsersLocalFile({ courseName }, student);
	}

	void Course::RemoveTeacher(const std::string& teacher)
	{
		teachers.erase(teacher);
		Factory::GetCourseFileManager()->RemoveTeacherFromCoursesInGlobalFile(teacher, std::vector<std::string> {courseName});
		Factory::GetCourseFileManager()->RemoveCoursesFromUsersLocalFile({ courseName }, teacher);
	}

	void Course::RemoveSelf()
	{
		for (auto& student : students)
		{
			Factory::GetCourseFileManager()->RemoveCoursesFromUsersLocalFile({ courseName }, student);
		}
		for (auto& teacher : teachers)
		{
			Factory::GetCourseFileManager()->RemoveCoursesFromUsersLocalFile({ courseName }, teacher);
		}

		Factory::GetCourseFileManager()->RemoveCourseFromGlobalFile(courseName);
		Departments::RemoveCourseFromDepartment(courseName, Departments::departmentOf(courseName));

		Factory::GetNotifierForCourseApplicationRequests(courseName)->DeleteCourseSubscription();
		PrerequisiteTypes::DeleteCourseSubscription(courseName);
	}

	void Course::NewPrerequisite(const Prerequisite& prerequisite)
	{
		prerequisites.emplace_back(prerequisite.clone());//todo clone

		PrerequisiteTypes::MakePrerequisitesForCourse(prerequisites, courseName);
	}

	void Course::RemovePrerequisite(const Prerequisite& prerequisite)
	{
		auto iterator = std::remove_if(prerequisites.begin(), prerequisites.end(),
			[&prerequisite](std::unique_ptr<Prerequisite>& obj)
			{
				return obj->GetConcreteDescription() == prerequisite.GetConcreteDescription();
			}
		);
		if (iterator != prerequisites.end())
			prerequisites.erase(iterator, prerequisites.end());

		PrerequisiteTypes::MakePrerequisitesForCourse(prerequisites, courseName);
	}

	std::string Course::getCourseTitle() const
	{
		return courseName;
	}

	bool Course::hasStudent(const std::string& username) const
	{
		return std::find(students.begin(), students.end(), username) != students.end();
	}

	bool Course::hasTeacher(const std::string& username) const
	{
		return std::find(teachers.begin(), teachers.end(), username) != teachers.end();
	}

	void Course::ApplyForRegistration(const std::string& username)
	{
		if (meetsPrerequisites(username))
		{
			Factory::GetNotifierForCourseApplicationRequests(courseName)->notify(username);
		}
		else
		{
			return;
		}
	}

	bool Course::meetsPrerequisites(const std::string& username) const
	{
		for (auto& prerequisite : prerequisites)
		{
			if (!prerequisite->metBy(username))
			{
				prerequisite->failMassage();
				return false;
			}
		}
		return true;
	}
}
