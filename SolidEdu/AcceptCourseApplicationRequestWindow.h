#pragma once

#include "IWindow.h"
#include <string>
#include <vector>
#include <iostream>

namespace solid_edu
{
	class AcceptCourseApplicationRequestWindow : public IWindow
	{
	private:
		std::unique_ptr<IUser> user;
		Course course;
		std::vector<std::string> requestSenders;

	public:
		AcceptCourseApplicationRequestWindow(std::unique_ptr<IUser> user, const Course& course,
			const std::vector<std::string>& requestSenders);

		std::unique_ptr<IWindow> runThenReturnWindow() override;
	};
}
