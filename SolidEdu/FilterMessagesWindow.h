#pragma once
#include "IWindow.h"

namespace solid_edu
{
	class FilterMessagesWindow : public IWindow
	{
	private:
		std::unique_ptr<IUser> user;

	public:
		FilterMessagesWindow(std::unique_ptr<IUser> user);
		
		std::unique_ptr<IWindow> runThenReturnWindow() override;
		
	};

}

