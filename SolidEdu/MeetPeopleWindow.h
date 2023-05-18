#pragma once

#include "IWindow.h"
#include "IUser.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

namespace solid_edu
{
	class MeetPeopleWindow : public IWindow
	{
	private:
		std::unique_ptr<IUser> user;

	public:
		MeetPeopleWindow(std::unique_ptr<IUser> user);

		std::unique_ptr<IWindow> runThenReturnWindow() override;

	private:
		std::vector<std::string> GetPeopleYouMayKnow();
	};
}

