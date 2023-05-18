#pragma once

#include "IWindow.h"

#include <iostream>

namespace solid_edu
{
	class TeacherAddOrRemovePrerequisitesWindow : public IWindow
	{
	private:
		std::unique_ptr<IUser> user;
		Course course;

	public:
		TeacherAddOrRemovePrerequisitesWindow(std::unique_ptr<IUser> user, const Course& course);

		std::unique_ptr<IWindow> runThenReturnWindow() override;
	};
}
