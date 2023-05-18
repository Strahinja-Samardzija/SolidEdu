#pragma once

#include "IWindow.h"
#include <iostream>

namespace solid_edu
{
	class AllCoursesWindow : public IWindow
	{
	private:
		std::unique_ptr<IUser> user;

	public:
		AllCoursesWindow(std::unique_ptr<IUser> user);

		std::unique_ptr<IWindow> runThenReturnWindow() override;
	};
}
