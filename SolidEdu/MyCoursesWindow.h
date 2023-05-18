#pragma once

#include "IWindow.h"
#include <iostream>

namespace solid_edu
{
	class MyCoursesWindow : public IWindow
	{
	private:
		std::unique_ptr<IUser> user;

	public:
		//todo check for all delete because there is no need
		MyCoursesWindow(std::unique_ptr<IUser> user);

		std::unique_ptr<IWindow> runThenReturnWindow() override;
	};
}
