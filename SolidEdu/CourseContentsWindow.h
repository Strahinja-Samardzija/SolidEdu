#pragma once

#include "IWindow.h"
#include "Course.h"
#include <iostream>

namespace solid_edu
{
	class CourseContentsWindow : public IWindow
	{
	private:
		Course course;
		std::unique_ptr<IUser> user;

	public:
		CourseContentsWindow(const Course& course, std::unique_ptr<IUser> user);

		std::unique_ptr<IWindow> runThenReturnWindow() override;
	};
}
