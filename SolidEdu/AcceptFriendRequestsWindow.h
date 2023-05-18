#pragma once

#include "IWindow.h"
#include "IUser.h"
#include <string>
#include <vector>
#include <iostream>

namespace solid_edu
{
	class AcceptFriendRequestsWindow : public IWindow
	{
	private:
		std::unique_ptr<IUser> user;
		std::vector<std::string> requests;

	public:
		AcceptFriendRequestsWindow(std::unique_ptr<IUser> user, const std::vector<std::string>& requests);

		std::unique_ptr<IWindow> runThenReturnWindow();
	};
}
