#pragma once
#include "IWindow.h"

namespace solid_edu
{
	class LoginWindow : public IWindow
	{
	private:
		static int triesCount;

	public:
		std::unique_ptr<IWindow> runThenReturnWindow() override;
	};
}
