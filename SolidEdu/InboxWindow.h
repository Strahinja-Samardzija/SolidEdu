#pragma once

#include "IWindow.h"
#include "IUser.h"
#include <string>
#include <vector>
#include <iostream>

namespace solid_edu
{
	class InboxWindow : public IWindow
	{
	private:
		std::unique_ptr<IUser> user;

	public:
		InboxWindow(std::unique_ptr<IUser> user);

		std::unique_ptr<IWindow> runThenReturnWindow() override;
	};
}
