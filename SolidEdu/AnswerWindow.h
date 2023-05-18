#pragma once

#include "IWindow.h"
#include "IUser.h"
#include <string>
#include <vector>
#include <iostream>
#include <memory>

namespace solid_edu
{
	class AnswerWindow : public IWindow
	{
	private:
		std::vector<std::string> peers;
		std::unique_ptr<IUser> user;

	public:
		AnswerWindow(std::vector<std::string>& peers, std::unique_ptr<IUser> user);

		std::unique_ptr<IWindow> runThenReturnWindow() override;

	};
}
