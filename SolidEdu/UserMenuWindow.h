#pragma once
#include <string>
#include <iostream>
#include <memory>
#include "IWindow.h"
#include "IUser.h"

namespace solid_edu
{
	class UserMenuWindow : public IWindow
	{
	private:
		std::unique_ptr<IUser> user;

	public:
		UserMenuWindow(std::unique_ptr<IUser> user);

		UserMenuWindow(const std::string& username);

		std::unique_ptr<IWindow> runThenReturnWindow() override;
	};
}
