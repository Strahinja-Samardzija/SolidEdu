#pragma once

#include "IWindow.h"
#include <string>
#include <iostream>

namespace solid_edu
{
	class StatsWindow : public IWindow
	{
	public:
		std::unique_ptr<IWindow> runThenReturnWindow() override;

	private:
		class NotRegistered {}; // exception class

		std::string getUser();

		std::string getCourse();

	};
}
