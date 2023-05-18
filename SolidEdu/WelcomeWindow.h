#pragma once

#include "IWindow.h"

namespace solid_edu
{
	class WelcomeWindow : public IWindow
	{
	public:
		std::unique_ptr<IWindow> runThenReturnWindow() override;
	};
}
