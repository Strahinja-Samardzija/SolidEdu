#pragma once

#include "PrerequisiteTypes.h"
#include "Course.h"
#include <iostream>

namespace solid_edu
{
	// this class is used by AdministratorWindows
	class CoursePrerequisiteModifier
	{
	private:
		Course course;

	public:
		CoursePrerequisiteModifier(const Course& course);
		
		// input from the console
		void RemovePrerequisite();

		// input from the console
		void AddPrerequisite();
	};
}

